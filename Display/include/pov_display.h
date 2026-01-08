#ifndef PoV_DISPLAY_H
#define PoV_DISPLAY_H

#include <FastLED.h>

struct ImageFrame
{
    // Image data: [row][column]
    // row = vertical position, column = LED index
    CRGB data[PoV_ROWS][NUM_LEDS];

    // Constructor
    ImageFrame()
    {
        clear();
    }

    // Clear all pixels
    void clear()
    {
        for (int row = 0; row < PoV_ROWS; row++)
        {
            for (int col = 0; col < NUM_LEDS; col++)
            {
                data[row][col] = CRGB::Black;
            }
        }
    }
};

class PoVDisplay
{
public:
    PoVDisplay();

    // Initialize the PoV display system
    void init();

    // Update display based on current rotation angle
    void update();

    // Set the image to display
    void setImage(const ImageFrame &image);

    // Get current display state (diagnostic)
    float getCurrentAngle();
    float getCurrentRPM();

    // Start/stop display
    void start();
    void stop();

private:
    ImageFrame currentImage;
    bool isRunning;
    float currentAngle;
    uint32_t lastUpdateTime;

    // Synchronize LEDs with rotation angle
    void syncLEDsToRotation();
};

#endif
