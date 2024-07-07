 #include <IRremote.h>
#define IR_RECEIVE_PIN 34
int forward = 12;
int reverse = 14;


void setup() {
  Serial.begin(9600);
  pinMode(forward,OUTPUT);
  pinMode(reverse,OUTPUT);
  //
  pinMode(35,OUTPUT);
  pinMode(35,HIGH);
  //
  digitalWrite(forward,LOW);
  digitalWrite(reverse,LOW);
  IrReceiver.begin(IR_RECEIVE_PIN); // Start the receiver
}

void loop() {
  unsigned long command;
  if (IrReceiver.decode()) {
    command = IrReceiver.decodedIRData.command;
      //Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
      // USE NEW 3.x FUNCTIONS
      IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
      
      if (command == 0x5A){
        Serial.println("clockwise");
        digitalWrite(reverse,LOW);
        delay(500);
        setMotorSpeed(forward);
        delay(100);
      } else if(command == 0x8) {
        Serial.println("anti-clockwise");
        digitalWrite(forward,LOW);
        delay(500);
        setMotorSpeed(reverse);
        delay(100);
      } else if(command == 0x1C) {
        Serial.println("stop!");
        digitalWrite(forward,LOW);
        digitalWrite(reverse,LOW);
        delay(100);
      } else{
        Serial.println("Left arrow for Anti-ClockWwise\nRightarrow for Clockwise\nOK to stop!");
      }
      IrReceiver.resume(); // Enable receiving of the next value
  }
  
}


void setMotorSpeed(int motorPin) {
  //pinMode(motorPin, OUTPUT);  // Set the motor pin as an output
  for (int speed = 128;speed<=255;speed++){
    analogWrite(motorPin, speed);  // Set the motor speed using PWM
    Serial.println(speed);
    delay(25);
  }
}