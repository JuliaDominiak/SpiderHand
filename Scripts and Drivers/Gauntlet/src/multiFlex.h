#include <Wire.h>
#include "SparkFun_Displacement_Sensor_Arduino_Library.h"

#pragma once

class MultiFlex
{
private:
    int numFlex;
    uint8_t *flexAdddresses;
    ADS *flexSensors;
    void (*callbackFn)(float, float, int, int) = NULL;

public:
    MultiFlex(int numFlex, uint8_t flexAdddresses[]);
    void begin();
    float getX(int sensorNum);
    float getY(int sensorNum);
    void setCallbackFn(void (*callbackFn)(float, float, int, int)); // x, y, address, num
    void loop();
};
