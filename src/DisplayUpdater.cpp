#include "DisplayUpdater.h"

#define sevenSeg0 0b01110111
#define sevenSeg1 0b00010100
#define sevenSeg2 0b10110011
#define sevenSeg3 0b10110110
#define sevenSeg4 0b11010100
#define sevenSeg5 0b11100110
#define sevenSeg6 0b11100111
#define sevenSeg7 0b00110100
#define sevenSeg8 0b11110111
#define sevenSeg9 0b11110110
#define sevenSegA 0b11110101
#define sevenSegB 0b11000111
#define sevenSegC 0b01100011
#define sevenSegD 0b10010111
#define sevenSegE 0b11100011
#define sevenSegF 0b11100001
#define sevenSegL 0b01000011
#define sevenSegR 0b10000001


void setDisplay(uint8_t display, uint8_t value, uint32_t* number) {
  *number &= ~(0b11111111 << (display * 8));
  *number |= (value << (display * 8));
}

void setDigit(uint8_t display, uint8_t value, uint32_t* number) {
  switch (value) {
    case 0:
      setDisplay(display, sevenSeg0, number);
      break;
    case 1:
      setDisplay(display, sevenSeg1, number);
      break;
    case 2:
      setDisplay(display, sevenSeg2, number);
      break;
    case 3:
      setDisplay(display, sevenSeg3, number);
      break;
    case 4:
      setDisplay(display, sevenSeg4, number);
      break;
    case 5:
      setDisplay(display, sevenSeg5, number);
      break;
    case 6:
      setDisplay(display, sevenSeg6, number);
      break;
    case 7:
      setDisplay(display, sevenSeg7, number);
      break;
    case 8:
      setDisplay(display, sevenSeg8, number);
      break;
    case 9:
      setDisplay(display, sevenSeg9, number);
      break;
    case 10:
      setDisplay(display, sevenSegA, number);
      break;
    case 11:
      setDisplay(display, sevenSegB, number);
      break;
    case 12:
      setDisplay(display, sevenSegC, number);
      break;
    case 13:
      setDisplay(display, sevenSegD, number);
      break;
    case 14:
      setDisplay(display, sevenSegE, number);
      break;
    case 15:
      setDisplay(display, sevenSegF, number);
      break;
    case 16:
      setDisplay(display, sevenSegL, number);
      break;
    case 17:
      setDisplay(display, sevenSegR, number);
      break;
    default:
      setDisplay(display, 0, number);
      break;
  }
}

void setDisplayToNumber(uint16_t value, uint32_t* number) {
  setDigit(3, value % 10, number);

  if (value > 9) {
    setDigit(2, (value / 10) % 10, number);
  } else {
    setDigit(2, 0xFF, number);
  }

  if (value > 99) {
    setDigit(1, (value / 100) % 10, number);
  } else {
    setDigit(1, 0xFF, number);
  }

  if (value > 999) {
    setDigit(0, (value / 1000) % 10, number);
  } else {
    setDigit(0, 0xFF, number);
  }
}



String getValue(String data, char separator, int index) {
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}