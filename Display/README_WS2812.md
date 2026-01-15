# FastLED WS2812 Example (Raspberry Pi Pico / Pico W)

Files added:

- files/ws2812_example.cpp

Wiring:

- Connect LED data line to GP2 (change `LED_PIN` in the example if you use a different pin).
- Connect LED V+ to 5V (or 3.3V if your strip supports it). Use a common ground between the Pico and the LED strip.
- Add a 300-500 ohm resistor in series with the data line for signal integrity and a capacitor (1000 µF) across V+ and GND for power smoothing.

How to build & upload:

```bash
platformio run --target upload
platformio device monitor --baud 115200
```

Notes:

- The project already lists `FastLED` in `platformio.ini` as `fastled/FastLED@^3.10.3`.
- Edit `LED_PIN`, `NUM_LEDS` and `BRIGHTNESS` at the top of `files/ws2812_example.cpp` to match your hardware.
- If you're using a Pico W board variant, ensure your `platformio.ini` board is correct for Pico W.
