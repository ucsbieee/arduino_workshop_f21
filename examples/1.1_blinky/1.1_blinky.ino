int LED_PIN = 5;

// Runs once at the start of your program
void setup() {
  // Make the LED pin an output (instead of an input)
  pinMode( LED_PIN, OUTPUT );

  // Initialize Serial communication to your computer (9600 bits per second)
  Serial.begin( 9600 );
}

// Runs over and over for the rest of time
void loop() {
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
