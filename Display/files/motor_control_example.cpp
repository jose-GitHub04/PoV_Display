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

#define IN1_PIN 2
#define IN2_PIN 3
#define ENB_PIN 4
int currentSpeed = 0;

void setup()
{
 Serial.begin(115200);
 delay(1000);

 Serial.println("\n=== L298N Motor Direct Control ===");
 Serial.println(" IN1=2, IN2=3");

 // Setup pins as outputs
 pinMode(ENB_PIN, OUTPUT);
 pinMode(IN1_PIN, OUTPUT);
 pinMode(IN2_PIN, OUTPUT);

 // Start with motor stopped
 digitalWrite(IN1_PIN, LOW);
 digitalWrite(IN2_PIN, LOW);

 Serial.println("Motor ready!");
 Serial.println("\nCommands:");
 Serial.println("  '+' - Increase speed by 20");
 Serial.println("  '-' - Decrease speed by 20");
 Serial.println("  'R' - Reverse direction");
 Serial.println("  'S' - Stop");
 Serial.println("  'D' - Print speed");
}

void loop()
{
 if (Serial.available() > 0)
 {
  char cmd = Serial.read();

  switch (cmd)
  {
  case '+':
   currentSpeed = constrain(currentSpeed + 20, -255, 255);
   Serial.print("Speed: ");
   Serial.println(currentSpeed);
   break;

  case '-':
   currentSpeed = constrain(currentSpeed - 20, -255, 255);
   Serial.print("Speed: ");
   Serial.println(currentSpeed);
   break;

  case 'r':
  case 'R':
   currentSpeed = -currentSpeed;
   Serial.print("Reversed! Speed: ");
   Serial.println(currentSpeed);
   break;

  case 's':
  case 'S':
   currentSpeed = 0;
   Serial.println("Stopped");
   break;

  case 'd':
  case 'D':
   Serial.print("Current speed: ");
   Serial.println(currentSpeed);
   break;

  default:
   break;
  }
 }
 digitalWrite(IN1_PIN, HIGH);
 digitalWrite(IN2_PIN, LOW);
 analogWrite(ENB_PIN, constrain(currentSpeed, 0, 255));
}
