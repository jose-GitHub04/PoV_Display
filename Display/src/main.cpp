#include <Arduino.h>
#include <FastLED.h>

// WS2812 LED strip configuration
#define LED_PIN 28
#define NUM_LEDS 24
#define BRIGHTNESS 128
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

// POV configuration
const uint16_t NUM_SLICES = 96; // angular resolution (columns)

// Hall sensor (index pulse) pin
#define HALL_PIN 15
// Number of hall pulses generated per full rotation (set to 2 if sensor sees both ends)
#define PULSES_PER_ROTATION 2

// motor control pins (unchanged)
#define IN1_PIN 2
#define IN2_PIN 3
#define ENB_PIN 4
int currentSpeed = 0;

CRGB leds[NUM_LEDS];

// Hall sensor is handled by include/hall_sensor.h / src/hall_sensor.cpp
#include "hall_sensor.h"

// Image matrix: slice (column) x row (LED index)
// We'll build a simple example matrix in setup() — you can replace this by converting an image.
CRGB imageMatrix[NUM_SLICES][NUM_LEDS];

// Initialize a simple image in the imageMatrix
void initializeImageMatrix()
{
 const uint16_t slicesPerColor = NUM_SLICES / 4; // Ensure even division of slices into 4 colors

 for (uint16_t slice = 0; slice < NUM_SLICES; ++slice)
 {
  for (uint16_t y = 0; y < NUM_LEDS; ++y)
  {
   uint16_t colorGroup = slice / slicesPerColor; // Divide slices into 4 equal groups

   if (y < NUM_LEDS / 2)
   {
    // First half of the bar
    switch (colorGroup)
    {
    case 0:
     imageMatrix[slice][y] = CRGB::Red;
     break;
    case 1:
     imageMatrix[slice][y] = CRGB::Blue;
     break;
    case 2:
     imageMatrix[slice][y] = CRGB::Green;
     break;
    case 3:
     imageMatrix[slice][y] = CRGB::Yellow;
     break;
    default:
     imageMatrix[slice][y] = CRGB::Black; // Fallback for any extra slices
     break;
    }
   }
   else
   {
    // Second half of the bar
    switch (colorGroup)
    {
    case 0:
     imageMatrix[slice][y] = CRGB::Blue;
     break;
    case 1:
     imageMatrix[slice][y] = CRGB::Yellow;
     break;
    case 2:
     imageMatrix[slice][y] = CRGB::Red;
     break;
    case 3:
     imageMatrix[slice][y] = CRGB::Green;
     break;
    default:
     imageMatrix[slice][y] = CRGB::Black; // Fallback for any extra slices
     break;
    }
   }
  }
 }
}

void setup()
{
 Serial.begin(115200);
 delay(100);

 // Motor control setup
 Serial.println("\n=== Motor Control + PoV Example ===");

 pinMode(ENB_PIN, OUTPUT);
 pinMode(IN1_PIN, OUTPUT);
 pinMode(IN2_PIN, OUTPUT);

 digitalWrite(IN1_PIN, LOW);
 digitalWrite(IN2_PIN, LOW);

 // FastLED setup
 FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
 FastLED.setBrightness(BRIGHTNESS);
 // Hall sensor init (debounce 1ms, history 8)
 hall_init(HALL_PIN, 1000, 48);

 // Initialize the image matrix
 initializeImageMatrix();
}

// Helper: display one slice (column)
void displaySlice(uint16_t slice)
{
 for (uint16_t y = 0; y < NUM_LEDS; ++y)
 {
  leds[y] = imageMatrix[slice][y];
 }
 FastLED.show();
}

void loop()
{
 unsigned long period_us;
 unsigned long switching_time_us = 0;
 if (hall_get_avg_period_us(&period_us))
 {
  // period_us is time between hall pulses; convert to full rotation period
  unsigned long rotation_period_us = period_us * (unsigned long)PULSES_PER_ROTATION;

  // Calculate the switching time for each slice
  switching_time_us = rotation_period_us / NUM_SLICES;

  // Print the switching time for debugging
  Serial.print("Switching time (us): ");
  Serial.println(switching_time_us);

  float freq = (rotation_period_us > 0) ? (1000000.0f / (float)rotation_period_us) : 0.0f;
  Serial.print("Rotation period (ms): ");
  Serial.println((float)rotation_period_us / 1000.0f, 2);
  Serial.print("Estimated frequency (Hz): ");
  Serial.println(freq, 2);
 }

 // Example: Display slices based on switching time
 for (uint16_t slice = 0; slice < NUM_SLICES; ++slice)
 {
  displaySlice(slice);
  delayMicroseconds(switching_time_us);
 }

 // Serial commands for motor control (unchanged)
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

 // Apply motor PWM (keep simple)
 digitalWrite(IN1_PIN, HIGH);
 digitalWrite(IN2_PIN, LOW);
 analogWrite(ENB_PIN, abs(constrain(currentSpeed, -255, 255)));
}
