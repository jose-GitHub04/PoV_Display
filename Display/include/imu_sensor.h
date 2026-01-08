#ifndef IMU_SENSOR_H
#define IMU_SENSOR_H

struct IMUData
{
    float accelX, accelY, accelZ;
    float gyroX, gyroY, gyroZ;
    float temperature;
};

class IMUSensor
{
public:
    IMUSensor();

    // Initialize IMU (I2C)
    bool init();

    // Read IMU data
    bool readData(IMUData &data);

    // Get current angular velocity (rotation speed)
    float getAngularVelocity();

    // Calculate current rotation angle based on gyro data
    float getRotationAngle();

    // Calibrate IMU (should be called when stationary)
    void calibrate();

    // Get gyro Z-axis (rotation around LED axis)
    float getGyroZ();

private:
    IMUData lastData;
    float rotationAngle;
    uint32_t lastUpdateTime;
};

#endif
