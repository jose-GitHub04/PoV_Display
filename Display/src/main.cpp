#include <Arduino.h>
#include <FastLED.h>

// WS2812 LED strip configuration
#define LED_PIN 28
#define NUM_LEDS 24
#define BRIGHTNESS 128
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

// motor control pins
#define IN1_PIN 2
#define IN2_PIN 3
#define ENB_PIN 4
int currentSpeed = 0;

CRGB leds[NUM_LEDS];

void setup()
{
 Serial.begin(115200);
 delay(100);
 // Motor control setup
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

 delay(100);
 // FastLED setup
 FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
 FastLED.setBrightness(BRIGHTNESS);
 Serial.println("FastLED WS2812 example started");
}

uint8_t hue = 0;

void loop()
{
 for (int i = 0; i < NUM_LEDS; ++i)
 {
  leds[i] = CHSV(hue + i * 8, 255, 255);
 }
 hue++;
 FastLED.show();
 delay(20);

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
