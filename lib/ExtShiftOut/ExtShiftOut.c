#include <ExtShiftOut.h>

void shiftOut16(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint16_t val) {
    uint8_t i;

    for(i = 0; i < 16; i++) {
        if(bitOrder == LSBFIRST) {
            digitalWrite(dataPin, !!(val & (1 << i)));
        }
        else {
            digitalWrite(dataPin, !!(val & (1 << (15 - i))));
        }

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

void shiftOut32(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint32_t val) {
    uint8_t i;

    for(i = 0; i < 32; i++) {
        if(bitOrder == LSBFIRST) {
            digitalWrite(dataPin, !!(val & (1 << i)));
        }
        else {
            digitalWrite(dataPin, !!(val & (1 << (31 - i))));
        }

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

void dualShiftOut(uint8_t dataPin1, uint8_t dataPin2, uint8_t clockPin, uint8_t bitOrder, uint8_t val1, uint8_t val2) {
    uint8_t i;

    for(i = 0; i < 8; i++) {
        if(bitOrder == LSBFIRST) {
            digitalWrite(dataPin1, !!(val1 & (1 << i)));
            digitalWrite(dataPin2, !!(val2 & (1 << i)));
        }
        else {
            digitalWrite(dataPin1, !!(val1 & (1 << (7 - i))));
            digitalWrite(dataPin2, !!(val2 & (1 << (7 - i))));
        }

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

void dualShiftOut16(uint8_t dataPin1, uint8_t dataPin2, uint8_t clockPin, uint8_t bitOrder, uint16_t val1, uint16_t val2) {
    uint8_t i;

    for(i = 0; i < 16; i++) {
        if(bitOrder == LSBFIRST) {
            digitalWrite(dataPin1, !!(val1 & (1 << i)));
            digitalWrite(dataPin2, !!(val2 & (1 << i)));
        }
        else {
            digitalWrite(dataPin1, !!(val1 & (1 << (15 - i))));
            digitalWrite(dataPin2, !!(val2 & (1 << (15 - i))));
        }

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

void dualShiftOut32(uint8_t dataPin1, uint8_t dataPin2, uint8_t clockPin, uint8_t bitOrder, uint32_t val1, uint32_t val2) {
    uint8_t i;

    for(i = 0; i < 32; i++) {
        if(bitOrder == LSBFIRST) {
            digitalWrite(dataPin1, !!(val1 & (1 << i)));
            digitalWrite(dataPin2, !!(val2 & (1 << i)));
        }
        else {
            digitalWrite(dataPin1, !!(val1 & (1 << (31 - i))));
            digitalWrite(dataPin2, !!(val2 & (1 << (31 - i))));
        }

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

void triShiftOut(uint8_t dataPin1, uint8_t dataPin2, uint8_t dataPin3, uint8_t clockPin, uint8_t bitOrder, uint8_t val1, uint8_t val2, uint8_t val3) {
    uint8_t i;

    for(i = 0; i < 8; i++) {
        if(bitOrder == LSBFIRST) {
            digitalWrite(dataPin1, !!(val1 & (1 << i)));
            digitalWrite(dataPin2, !!(val2 & (1 << i)));
            digitalWrite(dataPin3, !!(val3 & (1 << i)));
        }
        else {
            digitalWrite(dataPin1, !!(val1 & (1 << (7 - i))));
            digitalWrite(dataPin2, !!(val2 & (1 << (7 - i))));
            digitalWrite(dataPin3, !!(val3 & (1 << (7 - i))));
        }

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

void triShiftOut16(uint8_t dataPin1, uint8_t dataPin2, uint8_t dataPin3, uint8_t clockPin, uint8_t bitOrder, uint16_t val1, uint16_t val2, uint16_t val3) {
    uint8_t i;

    for(i = 0; i < 16; i++) {
        if(bitOrder == LSBFIRST) {
            digitalWrite(dataPin1, !!(val1 & (1 << i)));
            digitalWrite(dataPin2, !!(val2 & (1 << i)));
            digitalWrite(dataPin3, !!(val3 & (1 << i)));
        }
        else {
            digitalWrite(dataPin1, !!(val1 & (1 << (15 - i))));
            digitalWrite(dataPin2, !!(val2 & (1 << (15 - i))));
            digitalWrite(dataPin3, !!(val3 & (1 << (15 - i))));
        }

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

void triShiftOut32(uint8_t dataPin1, uint8_t dataPin2, uint8_t dataPin3, uint8_t clockPin, uint8_t bitOrder, uint32_t val1, uint32_t val2, uint32_t val3) {
    uint8_t i;

    for(i = 0; i < 32; i++) {
        if(bitOrder == LSBFIRST) {
            digitalWrite(dataPin1, !!(val1 & (1 << i)));
            digitalWrite(dataPin2, !!(val2 & (1 << i)));
            digitalWrite(dataPin3, !!(val3 & (1 << i)));
        }
        else {
            digitalWrite(dataPin1, !!(val1 & (1 << (31 - i))));
            digitalWrite(dataPin2, !!(val2 & (1 << (31 - i))));
            digitalWrite(dataPin3, !!(val3 & (1 << (31 - i))));
        }

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

void quadShiftOut(uint8_t dataPin1, uint8_t dataPin2, uint8_t dataPin3, uint8_t dataPin4, uint8_t clockPin, uint8_t bitOrder, uint8_t val1, uint8_t val2, uint8_t val3, uint8_t val4) {
    uint8_t i;

    for(i = 0; i < 8; i++) {
        if(bitOrder == LSBFIRST) {
            digitalWrite(dataPin1, !!(val1 & (1 << i)));
            digitalWrite(dataPin2, !!(val2 & (1 << i)));
            digitalWrite(dataPin3, !!(val3 & (1 << i)));
            digitalWrite(dataPin4, !!(val4 & (1 << i)));
        }
        else {
            digitalWrite(dataPin1, !!(val1 & (1 << (7 - i))));
            digitalWrite(dataPin2, !!(val2 & (1 << (7 - i))));
            digitalWrite(dataPin3, !!(val3 & (1 << (7 - i))));
            digitalWrite(dataPin4, !!(val4 & (1 << (7 - i))));
        }

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

void quadShiftOut16(uint8_t dataPin1, uint8_t dataPin2, uint8_t dataPin3, uint8_t dataPin4, uint8_t clockPin, uint8_t bitOrder, uint16_t val1, uint16_t val2, uint16_t val3, uint16_t val4) {
    uint8_t i;

    for(i = 0; i < 16; i++) {
        if(bitOrder == LSBFIRST) {
            digitalWrite(dataPin1, !!(val1 & (1 << i)));
            digitalWrite(dataPin2, !!(val2 & (1 << i)));
            digitalWrite(dataPin3, !!(val3 & (1 << i)));
            digitalWrite(dataPin4, !!(val4 & (1 << i)));
        }
        else {
            digitalWrite(dataPin1, !!(val1 & (1 << (15 - i))));
            digitalWrite(dataPin2, !!(val2 & (1 << (15 - i))));
            digitalWrite(dataPin3, !!(val3 & (1 << (15 - i))));
            digitalWrite(dataPin4, !!(val4 & (1 << (15 - i))));
        }

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

void quadShiftOut32(uint8_t dataPin1, uint8_t dataPin2, uint8_t dataPin3, uint8_t dataPin4, uint8_t clockPin, uint8_t bitOrder, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4) {
    uint8_t i;

    for(i = 0; i < 32; i++) {
        if(bitOrder == LSBFIRST) {
            digitalWrite(dataPin1, !!(val1 & (1 << i)));
            digitalWrite(dataPin2, !!(val2 & (1 << i)));
            digitalWrite(dataPin3, !!(val3 & (1 << i)));
            digitalWrite(dataPin4, !!(val4 & (1 << i)));
        }
        else {
            digitalWrite(dataPin1, !!(val1 & (1 << (31 - i))));
            digitalWrite(dataPin2, !!(val2 & (1 << (31 - i))));
            digitalWrite(dataPin3, !!(val3 & (1 << (31 - i))));
            digitalWrite(dataPin4, !!(val4 & (1 << (31 - i))));
        }

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

void multiShiftOut(uint8_t dataPins[], uint8_t pinCount, uint8_t clockPin, uint8_t bitOrder, uint8_t vals[]) {
    uint8_t i, j;

    for(i = 0; i < 8; i++) {
        if(bitOrder == LSBFIRST) {
            for (j = 0; j < pinCount; j++) {
                digitalWrite(dataPins[j], !!(vals[j] & (1 << i)));
            }
        }
        else {
            for (j = 0; j < pinCount; j++) {
                digitalWrite(dataPins[j], !!(vals[j] & (1 << (7 - i))));
            }
        }

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

void multiShiftOut16(uint8_t dataPins[], uint8_t pinCount, uint8_t clockPin, uint8_t bitOrder, uint16_t vals[]) {
    uint8_t i, j;

    for(i = 0; i < 16; i++) {
        if(bitOrder == LSBFIRST) {
            for (j = 0; j < pinCount; j++) {
                digitalWrite(dataPins[j], !!(vals[j] & (1 << i)));
            }
        }
        else {
            for (j = 0; j < pinCount; j++) {
                digitalWrite(dataPins[j], !!(vals[j] & (1 << (15 - i))));
            }
        }

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

void multiShiftOut32(uint8_t dataPins[], uint8_t pinCount, uint8_t clockPin, uint8_t bitOrder, uint32_t vals[]) {
    uint8_t i, j;

    for(i = 0; i < 32; i++) {
        if(bitOrder == LSBFIRST) {
            for (j = 0; j < pinCount; j++) {
                digitalWrite(dataPins[j], !!(vals[j] & (1 << i)));
            }
        }
        else {
            for (j = 0; j < pinCount; j++) {
                digitalWrite(dataPins[j], !!(vals[j] & (1 << (31 - i))));
            }
        }

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}