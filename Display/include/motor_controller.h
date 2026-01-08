#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

class MotorController
{
public:
    MotorController();

    // Initialize motor pins and PWM
    void init();

    // Set motor speed (0-255)
    // positive: clockwise, negative: counter-clockwise
    void setSpeed(int16_t speed);

    // Stop motor
    void stop();

    // Get current motor speed
    int16_t getSpeed();

    // Set motor direction
    void setDirection(bool clockwise);

private:
    int16_t currentSpeed;
    bool isClockwise;
};

#endif
