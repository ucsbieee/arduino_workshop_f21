#include "magic.h"

// Pins for talking to the shift register
int DATA_PIN = 4;
int CLOCK_PIN = 6;
int LATCH_PIN = 5;

int BUTTON_PIN = 3;

// Keep track of how many bits we're shifting by
// Start at -1 since we increment it once before displaying it
int8_t shift = -1;

// Keep track of the direction we're moving the LED
int dir = 1;

void setup() {
  pinMode( DATA_PIN, OUTPUT );
  pinMode( CLOCK_PIN, OUTPUT );
  pinMode( LATCH_PIN, OUTPUT );

  pinMode( BUTTON_PIN, INPUT_PULLUP );

  Serial.begin( 9600 );
}

void loop() {

  shift += dir; // Add (dir) to (shift) and store in (shift)

  // Reverse the direction of shifting when we get to the end of the LEDs
  if (shift == 7) {
    dir = -1; // Go the other way
    shift = 5; // Light the correct LED
  }
  if (shift == -1) {
    dir = 1;
    shift = 1;
  }

  uint8_t shifted = 1 << shift;

  Magic.printBinary( shifted );

  Magic.outputToShiftRegister( shifted, DATA_PIN, CLOCK_PIN, LATCH_PIN );

  // Delay so it doesn't go super fast
  delay( 1000 );
}
