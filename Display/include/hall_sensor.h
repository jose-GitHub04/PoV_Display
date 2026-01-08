#ifndef HALL_SENSOR_H
#define HALL_SENSOR_H

class HallSensor
{
public:
    HallSensor();

    // Initialize hall sensor pin
    void init();

    // Check if home position detected
    bool isHomeDetected();

    // Reset rotation counter
    void resetCounter();

    // Get number of home detections (rotations)
    uint32_t getRotationCount();

    // Callback when home position is detected
    void onHomeDetected();

private:
    volatile uint32_t rotationCount;
    volatile bool homeSignal;
};

#endif
