#include <Arduino.h>

// L298N Motor Driver Direct Control Example
// ==============================
// L298N pins:
//   - ENA (PWM speed control)   -> Arduino Pin 15
//   - IN1 (direction control)   -> Arduino Pin 2
//   - IN2 (direction control)   -> Arduino Pin 3
//
// Direction logic:
//   - IN1=HIGH, IN2=LOW  -> Clockwise
//   - IN1=LOW,  IN2=HIGH -> Counter-clockwise
//   - IN1=LOW,  IN2=LOW  -> Stop

void setup()
{
 Serial.begin(9600);
 pinMode(15, INPUT_PULLUP); // A0 as input
 delay(500);
}

void loop()
{

 // read input digital pin 15:
 int sensorValue = !digitalRead(15);

 // print out the value you read:
 Serial.print("Digital reading = ");
 Serial.println(sensorValue);

 delay(300);
}
