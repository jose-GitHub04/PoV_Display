#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <FastLED.h>

class LEDController
{
public:
    LEDController();

    // Initialize LED strip
    void init();

    // Set color for a specific LED
    void setLED(int index, CRGB color);

    // Set all LEDs to a specific color
    void setAll(CRGB color);

    // Clear all LEDs (set to black)
    void clear();

    // Update the LED display
    void show();

    // Set brightness (0-255)
    void setBrightness(uint8_t brightness);

    // Get pointer to LED array for direct manipulation
    CRGB *getLEDArray();

    // Get number of LEDs
    int getLEDCount();

private:
    CRGB leds[NUM_LEDS];
};

#endif
