# PoV Display Project - AI Coding Guidelines

## Motor Control Phase (Basic Complexity)

## Project Overview

This is a **Persistence of Vision (PoV) LED display** running on a **Raspberry Pi Pico** (PlatformIO + Arduino framework). Currently focusing on **motor control only** as the foundation. Additional modules (LED, IMU, Hall sensor) will be integrated gradually.

## Core Component: Motor Controller

**MotorController** (../include/motor_controller.h, ../src/motor_controller.cpp): Manages DC motor speed and direction via PWM and GPIO pins.

### Motor Pin Configuration

Located in ../include/config.h:

- **PWM Pin**: 15 (speed control via duty cycle 0-255)
- **Direction Pin**: 14 (logic level for clockwise/counter-clockwise)
- **Enable Pin**: 13 (motor enable/disable)

## Build & Debug Workflow

### PlatformIO Commands

```bash
platformio run           # Build for pico environment
platformio run --upload  # Build and upload to Pico
platformio device monitor # Serial monitor at 115200 baud
```

### Serial Commands (from main loop)

- `+`: Increase motor speed by 20
- `-`: Decrease motor speed by 20
- `D`: Print current motor speed to serial

Debug output: Motor speed printed to serial via `Serial.println()` in ../src/main.cpp

## Developer Patterns & Conventions

### Subsystem Initialization

All components follow standard pattern: `init()` method called from main.cpp setup phase. Currently only `motorController.init()` is active.

### Motor Control Philosophy

- Speed uses signed int16: **positive = clockwise, negative = counter-clockwise** (see ../include/motor_controller.h)
- Typical operating speed: 80% (MOTOR_MAX_SPEED \* 0.8 = 204/255) for smooth rotation
- Always call `motorController.stop()` to safely halt motor
- Speed range: 0-255 (0 = stopped, 255 = full power)

## Common Tasks & Examples

### Test Motor Speed Changes

1. Build and upload: `platformio run --upload`
2. Open serial monitor: `platformio device monitor`
3. Send `+` to increase speed by 20, or `-` to decrease
4. Send `D` to print current motor speed

### Tune Motor Speed

- Adjust `MOTOR_MAX_SPEED` in ../include/config.h
- Verify smooth rotation by observing motor behavior
- Test both clockwise (positive speed) and counter-clockwise (negative speed) directions

## External Dependencies

- **Arduino framework** (earlephilhower Pico core): System abstraction

## Critical Files & When to Modify

| File                          | Purpose                     | Modify when...                               |
| ----------------------------- | --------------------------- | -------------------------------------------- |
| ../include/config.h           | All constants/pins          | Changing hardware pins or target speed       |
| ../src/main.cpp               | Main loop & serial commands | Adding new user commands or startup sequence |
| ../include/motor_controller.h | Motor interface             | Changing motor API or adding features        |
| ../src/motor_controller.cpp   | Motor implementation        | Fixing motor control logic or PWM behavior   |
