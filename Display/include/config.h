#ifndef CONFIG_H
#define CONFIG_H

// ============================================
// PIN DEFINITIONS
// ============================================

// LED Strip (WS2812B/NeoPixel)
#define LED_PIN 2
#define NUM_LEDS 20

// Motor Control
#define MOTOR_PWM_PIN 15
#define MOTOR_DIR_PIN 14
#define MOTOR_ENABLE_PIN 13

// Hall Sensor (Home position reference)
#define HALL_SENSOR_PIN 3

// IMU (I2C)
#define IMU_SDA_PIN 4
#define IMU_SCL_PIN 5
#define IMU_ADDRESS 0x68 // MPU6050 default address

// ============================================
// CONFIGURATION PARAMETERS
// ============================================

// LED Configuration
#define LED_BRIGHTNESS 255
#define LED_UPDATE_RATE_HZ 100

// Motor Configuration
#define MOTOR_MAX_SPEED 255
#define MOTOR_MIN_SPEED 0

// PoV Display Configuration
#define PoV_RPM 60           // Target rotations per minute
#define PoV_COLUMNS NUM_LEDS // Number of LED columns
#define PoV_ROWS 100         // Height of image data (pixels)

// IMU Configuration
#define IMU_SAMPLE_RATE_HZ 200

// ============================================
// CONSTANTS
// ============================================

#define DEGREES_PER_LED (360.0f / NUM_LEDS)

#endif
