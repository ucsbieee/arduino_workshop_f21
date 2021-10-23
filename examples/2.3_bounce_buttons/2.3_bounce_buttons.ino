#include "magic.h"

// Pins for talking to the shift register
int DATA_PIN = 4;
int CLOCK_PIN = 6;
int LATCH_PIN = 5;

// Now have two buttons, one for each player
int PLAYER_1_BUTTON = 3;
int PLAYER_2_BUTTON = 2;

// Keep track of how many bits we're shifting by
// Start at -1 since we increment it once before displaying it
int8_t shift = -1;

// Keep track of the direction we're moving the LED
int dir = 1;

// Keep track of if the game is running
bool gameRunning = true;

void setup() {
  pinMode( DATA_PIN, OUTPUT );
  pinMode( CLOCK_PIN, OUTPUT );
  pinMode( LATCH_PIN, OUTPUT );

  pinMode( PLAYER_1_BUTTON, INPUT_PULLUP );
  pinMode( PLAYER_2_BUTTON, INPUT_PULLUP );

  Serial.begin( 9600 );
}

void loop() {
  if (gameRunning) {

    shift += dir; // Add (dir) to (shift) and store in (shift)

    // Reverse the direction of shifting when we get to the end of the LEDs
    if (shift == 7) {
      // Check if the player has the button pressed when the LED gets to their end
      if (digitalRead( PLAYER_1_BUTTON ) == LOW) {
        dir = -1; // Go the other way
        shift = 5; // Light the correct LED
      }
      else { // If they don't have it pressed, they lose!
        Serial.println( "Player 1 loses!" );
        gameRunning = false;
        return; // Don't run anything else in the loop
      }
    }
    if (shift == -1) {
      if (digitalRead( PLAYER_2_BUTTON ) == LOW) {
        dir = 1;
        shift = 1;
      }
      else {
        Serial.println( "Player 2 loses!" );
        gameRunning = false;
        return;
      }
    }

    uint8_t shifted = 1 << shift;

    Magic.printBinary( shifted );

    Magic.outputToShiftRegister( shifted, DATA_PIN, CLOCK_PIN, LATCH_PIN );

    // Delay so it doesn't go super fast
    delay( 1000 );
  }
}
