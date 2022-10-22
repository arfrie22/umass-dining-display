#ifndef DISPLAY_UPDATER_H
#define DISPLAY_UPDATER_H
#include <Arduino.h>

void setDisplay(uint8_t display, uint8_t value, uint32_t* number);
void setDigit(uint8_t display, uint8_t value, uint32_t* number);
void setDisplayToNumber(uint16_t value, uint32_t* number);
String getValue(String data, char separator, int index);

#endif // DISPLAY_UPDATER_H