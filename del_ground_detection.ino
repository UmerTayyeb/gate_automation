#define GROUND_PIN 4 // Define the pin number you are using to detect the ground connection
int x = 1;
void setup() {
  Serial.begin(115200);           // Initialize serial communication at 115200 baud rate
  pinMode(GROUND_PIN, INPUT_PULLUP); // Set the pin as input with an internal pull-up resistor
}

void loop() {
  int pinState = digitalRead(GROUND_PIN); // Read the state of the pin

  if (pinState == LOW) { // If the pin is connected to ground, the state will be LOW
    Serial.println("Pin is connected to ground");
    x = 0;
  } else {
    if (x == 1){
        Serial.println("Pin is not connected to ground");
    }
  }

  delay(500); // Wait for 1 second before checking again
}