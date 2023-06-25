#include "I2Cdev.h"
#include "MPU6050.h"

#pragma once

class Gyro{
    private:
    MPU6050 mpu;
    public:
    Gyro(){};
    explicit Gyro(uint8_t addr);
    void begin();
    void loop();
};