#include "MPU6050_6Axis_MotionApps20.h"

#pragma once

class Accel{
    private:
    MPU6050 mpu;
    uint8_t fifoBuffer[64];
    Quaternion q; 
    float euler[3]; 
    public:
    Accel();
    Accel(uint8_t addr);
    void begin();
    void loop();
};