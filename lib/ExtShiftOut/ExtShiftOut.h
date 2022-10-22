#ifndef EXT_SHIFT_OUT_H
#define EXT_SHIFT_OUT_H
#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

void shiftOut16(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint16_t val);
void shiftOut32(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint32_t val);

void dualShiftOut(uint8_t dataPin1, uint8_t dataPin2, uint8_t clockPin, uint8_t bitOrder, uint8_t val1, uint8_t val2);
void dualShiftOut16(uint8_t dataPin1, uint8_t dataPin2, uint8_t clockPin, uint8_t bitOrder, uint16_t val1, uint16_t val2);
void dualShiftOut32(uint8_t dataPin1, uint8_t dataPin2, uint8_t clockPin, uint8_t bitOrder, uint32_t val1, uint32_t val2);

void triShiftOut(uint8_t dataPin1, uint8_t dataPin2, uint8_t dataPin3, uint8_t clockPin, uint8_t bitOrder, uint8_t val1, uint8_t val2, uint8_t val3);
void triShiftOut16(uint8_t dataPin1, uint8_t dataPin2, uint8_t dataPin3, uint8_t clockPin, uint8_t bitOrder, uint16_t val1, uint16_t val2, uint16_t val3);
void triShiftOut32(uint8_t dataPin1, uint8_t dataPin2, uint8_t dataPin3, uint8_t clockPin, uint8_t bitOrder, uint32_t val1, uint32_t val2, uint32_t val3);

void quadShiftOut(uint8_t dataPin1, uint8_t dataPin2, uint8_t dataPin3, uint8_t dataPin4, uint8_t clockPin, uint8_t bitOrder, uint8_t val1, uint8_t val2, uint8_t val3, uint8_t val4);
void quadShiftOut16(uint8_t dataPin1, uint8_t dataPin2, uint8_t dataPin3, uint8_t dataPin4, uint8_t clockPin, uint8_t bitOrder, uint16_t val1, uint16_t val2, uint16_t val3, uint16_t val4);
void quadShiftOut32(uint8_t dataPin1, uint8_t dataPin2, uint8_t dataPin3, uint8_t dataPin4, uint8_t clockPin, uint8_t bitOrder, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4);

void multiShiftOut(uint8_t dataPins[], uint8_t pinCount, uint8_t clockPin, uint8_t bitOrder, uint8_t vals[]);
void multiShiftOut16(uint8_t dataPins[], uint8_t pinCount, uint8_t clockPin, uint8_t bitOrder, uint16_t vals[]);
void multiShiftOut32(uint8_t dataPins[], uint8_t pinCount, uint8_t clockPin, uint8_t bitOrder, uint32_t vals[]);

#ifdef __cplusplus
}
#endif

#endif // EXT_SHIFT_OUT_H
