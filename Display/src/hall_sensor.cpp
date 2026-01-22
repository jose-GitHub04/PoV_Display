#include "hall_sensor.h"

// Internal state
static volatile unsigned long last_pulse_us = 0;
static volatile unsigned long *period_history = nullptr;
static volatile uint8_t period_index = 0;
static volatile uint8_t period_count = 0;
static volatile uint8_t history_length = 0;
static volatile unsigned long min_pulse = 1000UL;
static volatile bool new_data = false;

static uint8_t hall_pin = 0;

static void hall_internal_isr();

void hall_init(uint8_t pin, unsigned long min_pulse_us, uint8_t history_len)
{
 hall_pin = pin;
 min_pulse = min_pulse_us;
 history_length = max((uint8_t)1, history_len);

 // allocate history buffer (malloc so sized at runtime)
 period_history = (unsigned long *)malloc(sizeof(unsigned long) * history_length);
 for (uint8_t i = 0; i < history_length; ++i)
  period_history[i] = 0;
 period_index = 0;
 period_count = 0;
 last_pulse_us = 0;
 new_data = false;

 pinMode(hall_pin, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(hall_pin), hall_internal_isr, FALLING);
}

// ISR: record dt if above debounce threshold
static void hall_internal_isr()
{
 unsigned long now = micros();
 if (last_pulse_us != 0)
 {
  unsigned long dt = now - last_pulse_us;
  if (dt >= min_pulse)
  {
   period_history[period_index] = dt;
   period_index = (period_index + 1) % history_length;
   if (period_count < history_length)
    period_count++;
   new_data = true;
  }
  // otherwise ignore
 }
 last_pulse_us = now;
}

bool hall_get_avg_period_us(unsigned long *period_us_out)
{
 if (!new_data)
  return false;

 // Snapshot buffer atomically
 noInterrupts();
 uint8_t count = period_count;
 unsigned long *local_buf = (unsigned long *)malloc(sizeof(unsigned long) * count);
 for (uint8_t i = 0; i < count; ++i)
  local_buf[i] = period_history[i];
 new_data = false;
 interrupts();

 if (count == 0)
 {
  free(local_buf);
  return false;
 }

 unsigned long sum = 0;
 for (uint8_t i = 0; i < count; ++i)
  sum += local_buf[i];
 free(local_buf);

 *period_us_out = sum / count;
 return true;
}
