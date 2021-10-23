#ifndef __MAGIC_H
#define __MAGIC_H

#include <Arduino.h>

struct magic_s {
  void printBinary( const uint8_t number ) const {
    Serial.print( "0b" );
    for (int8_t i = 7; i >= 0; i--)
      Serial.print( ( number >> i ) & 1 );
    Serial.println();
  }

  void outputToShiftRegister( const uint8_t data, const int dataPin, const int clockPin, const int latchPin ) const {
    digitalWrite( latchPin, LOW );
    shiftOut( dataPin, clockPin, LSBFIRST, data );
    digitalWrite( latchPin, HIGH );
  }
};

const magic_s Magic;

#endif
