#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ExtShiftOut.h>
#include <Hash.h>

#include "DisplayUpdater.h"
#include "LittleFS.h"
#include "values.h"

uint8_t macAddress[6] = {};

uint32_t data1 = 0;
uint32_t data2 = 0;
uint32_t data3 = 0;
uint32_t data4 = 0;

char ap_ssid[32] = "Dining Display xxxx";
char ap_password[64] = "123456789";

char station_ssid[32] = "UMASS-DEVICES";
char station_password[64] = "https://clearpass.it.umass.edu/guest/";

const char *headerKeys[] = {"Location"};
const size_t numberOfHeaders = 1;

bool debug = 0;

#define DISPLAY_UPDATE_INTERVAL 60

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

#define DATA_PIN1 16
#define DATA_PIN2 5
#define DATA_PIN3 4
#define DATA_PIN4 0

#define CLOCK_PIN 14
#define LATCH_PIN 12
#define ENABLE_PIN 13

String processor(const String &var) {
  if (var == "MAC_ADDRESS") {
    char macStr[18] = {0};

    sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", macAddress[0],
            macAddress[1], macAddress[2], macAddress[3], macAddress[4],
            macAddress[5]);
    return String(macStr);
  }

  if (var == "AP_SSID") {
    return LittleFS.exists("/ap_ssid")
               ? String(LittleFS.open("/ap_ssid", "r").readString())
               : "";
  }

  if (var == "AP_PSK") {
    return LittleFS.exists("/ap_psk")
               ? String(LittleFS.open("/ap_psk", "r").readString())
               : "";
  }

  if (var == "STATION_SSID") {
    return LittleFS.exists("/station_ssid")
               ? String(LittleFS.open("/station_ssid", "r").readString())
               : "";
  }

  if (var == "STATION_PSK") {
    return LittleFS.exists("/station_psk")
               ? String(LittleFS.open("/station_psk", "r").readString())
               : "";
  }

  return String();
}

void updateDisplay() {
  quadShiftOut32(DATA_PIN1, DATA_PIN2, DATA_PIN3, DATA_PIN4, CLOCK_PIN,
                 MSBFIRST, data1, data2, data3, data4);
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);
}

void clearDisplay() {
  data1 = 0;
  data2 = 0;
  data3 = 0;
  data4 = 0;
}

void setDisplayLoad() {
  setDigit(0, 16, &data1);
  setDigit(1, 0, &data1);
  setDigit(2, 10, &data1);
  setDigit(3, 13, &data1);

  setDigit(0, 16, &data2);
  setDigit(1, 0, &data2);
  setDigit(2, 10, &data2);
  setDigit(3, 13, &data2);

  setDigit(0, 16, &data3);
  setDigit(1, 0, &data3);
  setDigit(2, 10, &data3);
  setDigit(3, 13, &data3);

  setDigit(0, 16, &data4);
  setDigit(1, 0, &data4);
  setDigit(2, 10, &data4);
  setDigit(3, 13, &data4);
}

void setDisplayIpAddress() {
  IPAddress IP = WiFi.softAPIP();
  setDisplayToNumber(IP[0], &data1);
  setDisplayToNumber(IP[1], &data2);
  setDisplayToNumber(IP[2], &data3);
  setDisplayToNumber(IP[3], &data4);

  data1 |= 1 << 27;
  data2 |= 1 << 27;
  data3 |= 1 << 27;
}

void debugAp() {
  if (debug) return;

  debug = 1;
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ap_ssid, ap_password);

  WiFi.setHostname("dining-display");

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());
  setDisplayIpAddress();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/public/index.html", String(), false);
  });
  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/public/index.html", String(), false);
  });
  server.on("/main.html", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/public/main.html", String(), false, processor);
  });
  server.on("/update-wifi.html", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/public/update-wifi.html", String(), false,
                  processor);
  });
  server.on("/update-softap.html", HTTP_GET,
            [](AsyncWebServerRequest *request) {
              request->send(LittleFS, "/public/update-softap.html", String(),
                            false, processor);
            });
  server.on("/css/primer.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse(
        LittleFS, "/public/css/primer.css.gz", String("text/css"));
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  server.on("/css/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/public/css/style.js");
  });
  server.on("/js/theme.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/public/js/theme.js");
  });
  server.on("/js/common.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/public/js/common.js");
  });

  server.on("/update-wifi", HTTP_POST, [](AsyncWebServerRequest *request) {
    String mac = request->getParam("mac-address", true)->value();
    String ssid = request->getParam("ssid", true)->value();
    String psk = request->getParam("psk", true)->value();

    if (mac.length() != 17) {
      request->send_P(
          400, "text/plain",
          String("Invalid mac address length of " + String(mac.length()) +
                 ", the length should be 17 characters")
              .c_str());
      return;
    }

    if (ssid.length() == 0) {
      request->send_P(400, "text/plain", "SSID cannot be empty");
      return;
    }

    if (ssid.length() > 32) {
      request->send_P(400, "text/plain",
                      "SSID cannot be longer than 32 characters");
      return;
    }

    if (psk.length() < 8) {
      request->send_P(400, "text/plain", "PSK must be at least 8 characters");
      return;
    }

    if (psk.length() > 64) {
      request->send_P(400, "text/plain",
                      "PSK cannot be longer than 64 characters");
      return;
    }

    for (int i = 0; i < 6; i++) {
      macAddress[i] =
          (uint8_t)strtol(mac.substring(i * 3, i * 3 + 2).c_str(), NULL, 16);
    }

    char macStr[18] = {0};

    sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", macAddress[0],
            macAddress[1], macAddress[2], macAddress[3], macAddress[4],
            macAddress[5]);

    wifi_set_macaddr(STATION_IF, &macAddress[0]);

    File file = LittleFS.open("/mac_address", "w");
    file.write(macAddress, 6);
    file.close();

    file = LittleFS.open("/ap_ssid", "w");
    file.write(ssid.c_str(), ssid.length());
    file.close();

    file = LittleFS.open("/ap_psk", "w");
    file.write(psk.c_str(), psk.length());
    file.close();

    request->send_P(200, "text/plain", "WiFi Info Updated");
  });

  server.on("/update-softap", HTTP_POST, [](AsyncWebServerRequest *request) {
    String ssid = request->getParam("ssid", true)->value();
    String psk = request->getParam("psk", true)->value();

    if (ssid.length() == 0) {
      request->send_P(400, "text/plain", "SSID cannot be empty");
      return;
    }

    if (ssid.length() > 32) {
      request->send_P(400, "text/plain",
                      "SSID cannot be longer than 32 characters");
      return;
    }

    if (psk.length() < 8) {
      request->send_P(400, "text/plain", "PSK must be at least 8 characters");
      return;
    }

    if (psk.length() > 64) {
      request->send_P(400, "text/plain",
                      "PSK cannot be longer than 64 characters");
      return;
    }

    File file = LittleFS.open("/ap_ssid", "w");
    file.write(ssid.c_str(), ssid.length());
    file.close();

    file = LittleFS.open("/ap_psk", "w");
    file.write(psk.c_str(), psk.length());
    file.close();

    request->send_P(200, "text/plain", "WiFi Info Updated");
  });

  server.on("/restart", HTTP_POST, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", "Restarting");
    ESP.restart();
  });

  // Start server
  server.begin();
}

String requestURL(String url) {
  int index = url.indexOf(':');

  String protocol = url.substring(0, index);
  protocol.toLowerCase();

  WiFiClientSecure client_s;
  WiFiClient client;

  HTTPClient http;

  if (protocol == "https") {
    client_s = WiFiClientSecure();
    client_s.setInsecure();
    http.begin(client_s, url);
  } else {
    client = WiFiClient();
    http.begin(client, url);
  }

  // Your Domain name with URL path or IP address with path
  http.collectHeaders(headerKeys, numberOfHeaders);

  http.setUserAgent(
      "Mozilla/5.0 (Nintendo Switch; WifiWebAuthApplet) AppleWebKit/609.4 "
      "(KHTML, like Gecko) NF/6.0.2.20.5 NintendoBrowser/5.1.0.22023");

  // Send HTTP GET request
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    String loc = http.header("Location");
    if (loc.indexOf("clearpass", 0) > 0) {
      http.end();
      debugAp();
      Serial.println("Clearpass detected, setting up AP");
      return loc;
    }

    String payload = http.getString();
    http.end();
    return payload;
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    http.end();
    return "";
  }
}

void updateTotals() {
  if (debug) return;
  String res = requestURL("http://vm1.yyz1.hammy.network:8090/arduino");
  if (!strcmp(res.c_str(), "")) {
    Serial.println("Error getting data");
    updateTotals();
    return;
  }

  setDisplayToNumber(atoi(getValue(res, '\n', 0).c_str()), &data1);
  setDisplayToNumber(atoi(getValue(res, '\n', 1).c_str()), &data2);
  setDisplayToNumber(atoi(getValue(res, '\n', 2).c_str()), &data3);
  setDisplayToNumber(atoi(getValue(res, '\n', 3).c_str()), &data4);
}

void setup() {
  // Start serial
  Serial.begin(115200);

  // Setup pins
  pinMode(DATA_PIN1, OUTPUT);
  pinMode(DATA_PIN2, OUTPUT);
  pinMode(DATA_PIN3, OUTPUT);
  pinMode(DATA_PIN4, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  // Initalize latch and enable pins
  digitalWrite(LATCH_PIN, LOW);
  digitalWrite(ENABLE_PIN, LOW);

  // Set display to say "LOAD"
  setDisplayLoad();
  updateDisplay();

  // Setup LittleFS
  LittleFS.begin();

  // Setup WiFi Mac Address
  WiFi.macAddress(macAddress);
  if (LittleFS.exists("/mac_address")) {
    // If the mac address file exists, read it and set the mac address
    Serial.println("MAC address found");
    File file = LittleFS.open("/mac_address", "r");
    int bytesRead = file.read(macAddress, 6);
    file.close();

    if (bytesRead != 6) {
      // If the file is not 6 bytes, set the mac address to the default
      WiFi.macAddress(macAddress);
      char macStr[18] = {0};
      sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", macAddress[0],
              macAddress[1], macAddress[2], macAddress[3], macAddress[4],
              macAddress[5]);
      Serial.println("Error reading MAC address, resetting value to: " +
                     String(macStr));
      File file = LittleFS.open("/mac_address", "w");
      file.write(macAddress, 6);
      file.close();
    } else {
      // If the file is 6 bytes, set the mac address to the value in the file
      char macStr[18] = {0};
      sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", macAddress[0],
              macAddress[1], macAddress[2], macAddress[3], macAddress[4],
              macAddress[5]);
      Serial.println("Setting MAC address to: " + String(macStr));
      wifi_set_macaddr(STATION_IF, &macAddress[0]);
    }
  } else {
    // If the mac address file doesn't exist, create it and set the mac address
    File file = LittleFS.open("/mac_address", "w");
    Serial.println("MAC Address not set, setting to: " +
                   String(WiFi.macAddress()));
    file.write(macAddress, 6);
    file.close();
  }

  String id_str = String((uint16_t)random(0xFFFF), HEX);
  id_str.toUpperCase();
  ap_ssid[15] = id_str[0];
  ap_ssid[16] = id_str[1];
  ap_ssid[17] = id_str[2];
  ap_ssid[18] = id_str[3];

  if (LittleFS.exists("/ap_ssid")) {
    File file = LittleFS.open("/ap_ssid", "r");
    int bytesRead = file.readBytes(ap_ssid, 32);

    if (bytesRead == 0) {
      Serial.println("Error reading AP SSID, resetting value");
      File file = LittleFS.open("/ap_ssid", "w");
      file.write(ap_ssid, 32);
      file.close();
    } else {
      Serial.println("Setting AP SSID to: " + String(ap_ssid));
    }
  } else {
    File file = LittleFS.open("/ap_ssid", "w");
    file.write(ap_ssid, 32);
    file.close();
  }

  if (LittleFS.exists("/ap_psk")) {
    File file = LittleFS.open("/ap_psk", "r");
    int bytesRead = file.readBytes(ap_password, 64);

    if (bytesRead == 0) {
      Serial.println("Error reading AP PSK, resetting value");
      File file = LittleFS.open("/ap_psk", "w");
      file.write(ap_password, 64);
      file.close();
    } else {
      Serial.println("Setting AP PSK to: " + String(ap_password));
    }
  } else {
    File file = LittleFS.open("/ap_psk", "w");
    file.write(ap_password, 64);
    file.close();
  }

  if (LittleFS.exists("/station_ssid")) {
    File file = LittleFS.open("/station_ssid", "r");
    int bytesRead = file.readBytes(station_ssid, 32);

    if (bytesRead == 0) {
      Serial.println("Error reading Station SSID, resetting value");
      File file = LittleFS.open("/station_ssid", "w");
      file.write(station_ssid, 32);
      file.close();
    } else {
      Serial.println("Setting Station SSID to: " + String(station_ssid));
    }
  } else {
    File file = LittleFS.open("/station_ssid", "w");
    file.write(station_ssid, 32);
    file.close();
  }

  if (LittleFS.exists("/station_psk")) {
    File file = LittleFS.open("/station_psk", "r");
    int bytesRead = file.readBytes(station_password, 64);

    if (bytesRead == 0) {
      Serial.println("Error reading Station PSK, resetting value");
      File file = LittleFS.open("/station_psk", "w");
      file.write(station_password, 64);
      file.close();
    } else {
      Serial.println("Setting Station PSK to: " + String(station_password));
    }
  } else {
    File file = LittleFS.open("/station_psk", "w");
    file.write(station_password, 64);
    file.close();
  }

  // Setup WiFi
  WiFi.mode(WIFI_STA);
  wifi_set_macaddr(STATION_IF, &macAddress[0]);

  WiFi.begin(station_ssid, station_password);

  Serial.println("MAC address is: " + WiFi.macAddress());
  Serial.print("Connecting");
  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED) {
    if (timeout > 60) {
      Serial.println("Failed to connect to WiFi, starting AP");
      debugAp();
      return;
    }

    delay(500);
    Serial.print(".");
    timeout++;
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  String res = requestURL("https://example.com");

  updateTotals();
  updateDisplay();
}

long lastUpdate = 0;
void loop() {
  // Update totals every DISPLAY_UPDATE_INTERVAL seconds
  if ((!debug) && (millis() - lastUpdate > 1000 * DISPLAY_UPDATE_INTERVAL)) {
    updateTotals();
    lastUpdate = millis();
  }

  updateDisplay();
}