#include "magic.h"

// Pins for talking to the shift register
int DATA_PIN = 4;
int CLOCK_PIN = 6;
int LATCH_PIN = 5;

int BUTTON_PIN = 3;

// Keep track of how many bits we're shifting by
int8_t shift = 0;

void setup() {
  pinMode( DATA_PIN, OUTPUT );
  pinMode( CLOCK_PIN, OUTPUT );
  pinMode( LATCH_PIN, OUTPUT );

  pinMode( BUTTON_PIN, INPUT_PULLUP );

  Serial.begin( 9600 );
}

void loop() {
  // Only shift stuff when the button is pressed
  if (digitalRead( BUTTON_PIN ) == LOW) {
    // Shift a 1 to the left by (shift) number of bits
    uint8_t shifted = 1 << shift;

    // Print out the number in binary (function from Magic.h)
    Magic.printBinary( shifted );

    // Output the number to the shift register to display its bits as LEDs
    //   (we'll explain how this works at the end, time permitting)
    Magic.outputToShiftRegister( shifted, DATA_PIN, CLOCK_PIN, LATCH_PIN );

    // Increment the number of bits to shift
    shift++;

    // Reset shift back to zero when it gets to 7
    if (shift == 7)
      shift = 0;

    // Delay so it doesn't go super fast
    delay( 1000 );
  }
}
