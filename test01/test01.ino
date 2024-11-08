#define GROUND_PIN_1 2 // Define the pin number you are using to detect the ground connection
#define GROUND_PIN_2 4 // remote control

#define GROUND_PIN_3 7 // Define the pin number you are using to detect the ground connection
#define GROUND_PIN_4 8 // Stop signal

int forward = 9;
int reverse = 10;
int starting_speed = 128;
int final_speed = 192;
bool isRunningClockwise = false;
bool isRunningAnticlockwise = false;


void setup() {
  Serial.begin(115200);
  Serial.println("setup");
  pinMode(forward,OUTPUT);
  pinMode(reverse,OUTPUT);
  
  pinMode(GROUND_PIN_1, INPUT_PULLUP); // Set the pin as input with an internal pull-up resistor
  pinMode(GROUND_PIN_2, INPUT_PULLUP); // remote control

  pinMode(GROUND_PIN_3, INPUT_PULLUP); // Set the pin as input with an internal pull-up resistor
  pinMode(GROUND_PIN_4, INPUT_PULLUP); // Stop signal

  digitalWrite(forward,LOW);
  digitalWrite(reverse,LOW);
  
}

void loop() {
  int pinState1 = digitalRead(GROUND_PIN_1); // Read the state of the pin
  int pinState2 = digitalRead(GROUND_PIN_2); // remote control

  int pinState3 = digitalRead(GROUND_PIN_3); // Read the state of the pin
  int pinState4 = digitalRead(GROUND_PIN_4); // Stop signal
  
  
  int sensorValue = analogRead(A6); // Read the current input on analog pin A1
  float voltage = sensorValue*5/1023.0;
  float current = (voltage-2.5)/0.066;
  if(current < 0.20){
    current = 0;
  }

  if(current < 2.00){    //this function will run the code for opening, closing and stopping the gate.  
    // Serial.println(current);

    if (!isRunningAnticlockwise && pinState1 == LOW){
      Serial.println("clockwise");
      isRunningClockwise = true;
      digitalWrite(reverse,LOW);
      delay(500);
      setMotorSpeed(forward);
      delay(100);

    } if(!isRunningClockwise && pinState2 == LOW) {
      Serial.println("anti-clockwise");
      isRunningAnticlockwise = true;
      digitalWrite(forward,LOW);
      delay(500);
      setMotorSpeed(reverse);
      delay(100);

    } if(pinState3 == LOW || pinState4 == LOW) {
      Serial.println("stop!");
      stopMotor(1000);

    } if(isRunningClockwise && pinState2 == LOW)||(isRunningAnticlockwise && pinState1 == LOW){
        Serial.println("Stopping motor immediately");
        stopMotor(1000);
        delay(2000);
        return;

    } 
  } else if(current > 2.00){
    stopMotor(0);
    delay(1000);
  }
}
  
  void setMotorSpeed(int motorPin) {
    //pinMode(motorPin, OUTPUT);  // Set the motor pin as an output
    for (int speed = starting_speed; speed<=final_speed; speed++){
      analogWrite(motorPin, speed);  // Set the motor speed using PWM
      // Serial.println(speed);
      delay(25);
    }
  }


  void stopMotor(int wait_delay) {
  digitalWrite(forward, HIGH);
  digitalWrite(reverse, HIGH);
  delay(wait_delay);
  digitalWrite(forward, LOW);
  digitalWrite(reverse, LOW);
  
  // Reset direction flags
  isRunningClockwise = false;
  isRunningAnticlockwise = false;
}