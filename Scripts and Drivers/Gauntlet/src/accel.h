#include "MPU6050.h"

#pragma once

class Accel{
    private:
    MPU6050 mpu;
    public:
    Accel(){};
    Accel(uint8_t addr);
    void begin();
    void loop();
};