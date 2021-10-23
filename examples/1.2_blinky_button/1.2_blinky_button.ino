int LED_PIN = 5;
int BUTTON_PIN = 3;

// Runs once at the start of your program
void setup() {
  pinMode( LED_PIN, OUTPUT );
  pinMode( BUTTON_PIN, INPUT_PULLUP );

  Serial.begin( 9600 );
}

// Runs over and over for the rest of time
void loop() {
  // Only flash the LED if the button is pressed
  //   LOW state means button is pressed because
  //   the button is connected to GND and pull-up
  //   makes it HIGH otherwise
  if (digitalRead( BUTTON_PIN ) == LOW) {
    // Turn on the LED
    digitalWrite( LED_PIN, HIGH );

    // Send a message saying the LED was turned on
    Serial.println( "LED on" );

    // Wait 0.5 seconds (500 milliseconds)
    delay( 500 );

    // Turn the LED off again and wait
    digitalWrite( LED_PIN, LOW );
    Serial.println( "LED off" );

    // Wait 0.5 seconds again
    delay( 500 );
  }
}
