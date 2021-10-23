int LED_PIN = 5; // PWM only works on certain pins
int BUTTON_PIN = 3;

// Make an 8-bit integer that stores the brightness of the LED
uint8_t brightness = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  // Only make the LED brighter when the button is pressed
  if(digitalRead(BUTTON_PIN) == LOW) {
    // Use PWM to set the brightness of the LED
    analogWrite(LED_PIN, brightness);

    // Say how bright the LED is
    Serial.println("brightness = " + String(brightness));

    // Increment the brightness
    brightness++;

    // Delay so it doesn't go super fast
    delay(10);
  }
}
