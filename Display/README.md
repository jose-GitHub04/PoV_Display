# Files Directory Overview

This files are examples to work with each hardware part independently, just as a way to learn each component.

- **`ws2812_example.cpp`**: This file contains an example implementation for controlling WS2812 LED strips using the FastLED library. It demonstrates how to configure and control the LEDs, including setting the pin, number of LEDs, and brightness.
- **`hall_sensor_example.cpp`**: This file provides an example of how to use a hall sensor with the project. It includes code for reading data from the sensor and processing it.
- **`motor_control_example.cpp`**: This file contains example code for controlling a motor, which may be used in conjunction with the PoV Display project.
- **`image_to_c.py`**: A Python script that converts image files into C arrays, which can be used for displaying images on the LED strip.

## Notes

- The project already includes the `FastLED` library in the `platformio.ini` file as `fastled/FastLED@^3.10.3`.
