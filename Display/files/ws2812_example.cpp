#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN 28
#define NUM_LEDS 24
#define BRIGHTNESS 128
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

void setup()
{
 Serial.begin(115200);
 delay(100);
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
}
