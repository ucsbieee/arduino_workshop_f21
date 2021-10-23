#include "magic.h"

int LED_PIN = 5;
int BUTTON_PIN = 3;

// Keep track of how many bits we're shifting by
uint8_t shift = 0;

void setup() {
  pinMode( LED_PIN, OUTPUT );
  pinMode( BUTTON_PIN, INPUT_PULLUP );

  Serial.begin( 9600 );
}

void loop() {
  // Only shift stuff when the button is pressed
  if (digitalRead( BUTTON_PIN ) == LOW) {
    // Shift a 1 to the left by (shift) number of bits
    uint8_t shifted = 1 << shift;

    // Print out the number in binary (function from magic.h)
    Magic.printBinary( shifted );

    // Turn on the LED if the 3rd bit from the right is a 1
    bool bit3 = shifted & 0b00000100;
    digitalWrite( LED_PIN, bit3 );

    // Increment the number of bits to shift
    shift++;

    // Reset shift back to zero when it gets to 8
    if (shift == 8)
      shift = 0;

    // Delay so it doesn't go super fast
    delay( 1000 );
  }
}
