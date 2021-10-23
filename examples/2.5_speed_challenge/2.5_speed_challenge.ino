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

// How many ms between when the LED moves
unsigned long wait = 1000; // 1s to start with
const float speedIncrease = 0.9; // (wait) decreases by 10% each time!

// Keep track of the state of the buttons
volatile bool p1PaddleUp = false;
volatile bool p2PaddleUp = false;

void setup() {
  pinMode( DATA_PIN, OUTPUT );
  pinMode( CLOCK_PIN, OUTPUT );
  pinMode( LATCH_PIN, OUTPUT );

  pinMode( PLAYER_1_BUTTON, INPUT_PULLUP );
  pinMode( PLAYER_2_BUTTON, INPUT_PULLUP );

  // Connect buttons to interrupts that will interrupt
  //   the current code execution to run the interrupt
  //   handler function on the FALLING edge of the pin
  //   (when it goes from high to low, or unpressed to pressed)
  // These are only available on certain pins (2 and 3 for this Arduino)
  attachInterrupt( digitalPinToInterrupt( PLAYER_1_BUTTON ), handlePlayer1Button, FALLING );
  attachInterrupt( digitalPinToInterrupt( PLAYER_2_BUTTON ), handlePlayer2Button, FALLING );

  Serial.begin( 9600 );
}

void loop() {
  if (gameRunning) {

    shift += dir; // Add (dir) to (shift) and store in (shift)

    // Reverse the direction of shifting when we get to the end of the LEDs
    bool bounce = false;
    if (shift == 7) {
      // Check if the player has pressed the button while the last LED was lit
      if (p1PaddleUp) {
        dir = -1; // Go the other way
        shift = 5; // Light the correct LED
        bounce = true; // Keep track of a successful bounce
      }
      else { // If they don't have it pressed, they lose!
        Serial.println( "Player 1 loses!" );
        gameRunning = false;
        return; // Don't run anything else in the loop
      }
    }
    if (shift == -1) {
      if (p2PaddleUp) {
        dir = 1;
        shift = 1;
        bounce = true;
      }
      else {
        Serial.println( "Player 2 loses!" );
        gameRunning = false;
        return;
      }
    }

    // Increase speed if there was a bounce!
    if (bounce) {
      wait *= speedIncrease;
      Serial.println( "Delay is now " + String( wait ) + "ms" );
    }

    // Reset button flags so you can't press the button early
    p1PaddleUp = false;
    p2PaddleUp = false;

    uint8_t shifted = 1 << shift;

    Magic.outputToShiftRegister( shifted, DATA_PIN, CLOCK_PIN, LATCH_PIN );

    // Delay so it eventually goes super fast
    delay( wait );
  }
}

// Called whenever player 1 presses their button
void handlePlayer1Button() {
  p1PaddleUp = true;
}

// Called whenever player 2 presses their button
void handlePlayer2Button() {
  p2PaddleUp = true;
}
