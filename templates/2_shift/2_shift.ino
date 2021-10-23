#include "magic.h"

// Pins for talking to the shift register
int DATA_PIN = 4;
int CLOCK_PIN = 6;
int LATCH_PIN = 5;

// Now have two buttons, one for each player
int PLAYER_1_BUTTON = 3;
int PLAYER_2_BUTTON = 2;

uint8_t shift = 0;

void setup() {
  Serial.begin( 9600 );
}

void loop() {

}
