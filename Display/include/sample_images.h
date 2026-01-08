#ifndef SAMPLE_IMAGES_H
#define SAMPLE_IMAGES_H

#include "pov_display.h"

// Simple test pattern: vertical bars of different colors
ImageFrame createTestPattern()
{
    ImageFrame frame;

    for (int row = 0; row < PoV_ROWS; row++)
    {
        for (int col = 0; col < NUM_LEDS; col++)
        {
            // Create color based on column
            if (col % 2 == 0)
            {
                frame.data[row][col] = CRGB::Red;
            }
            else
            {
                frame.data[row][col] = CRGB::Blue;
            }
        }
    }

    return frame;
}

// Gradient pattern
ImageFrame createGradient()
{
    ImageFrame frame;

    for (int row = 0; row < PoV_ROWS; row++)
    {
        for (int col = 0; col < NUM_LEDS; col++)
        {
            // Create gradient from bottom to top
            uint8_t brightness = (row * 255) / PoV_ROWS;
            frame.data[row][col] = CRGB(brightness, brightness / 2, 0);
        }
    }

    return frame;
}

// Checkerboard pattern
ImageFrame createCheckerboard()
{
    ImageFrame frame;

    for (int row = 0; row < PoV_ROWS; row++)
    {
        for (int col = 0; col < NUM_LEDS; col++)
        {
            if ((row + col) % 2 == 0)
            {
                frame.data[row][col] = CRGB::White;
            }
            else
            {
                frame.data[row][col] = CRGB::Black;
            }
        }
    }

    return frame;
}

#endif
