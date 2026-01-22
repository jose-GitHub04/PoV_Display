#ifndef HALL_SENSOR_H
#define HALL_SENSOR_H

#include <Arduino.h>

// Initialize hall sensor on given pin. min_pulse_us filters pulses shorter than this (debounce)
void hall_init(uint8_t pin, unsigned long min_pulse_us = 1000, uint8_t history_length = 8);

// If a new averaged period is available, returns true and writes period_us (microseconds).
// This consumes the "new" flag.
bool hall_get_avg_period_us(unsigned long *period_us_out);

// Compute rpm from period in microseconds
static inline float hall_rpm_from_period_us(unsigned long period_us)
{
 return (period_us > 0) ? (60000000.0f / (float)period_us) : 0.0f;
}

#endif // HALL_SENSOR_H
