#include "multiFlex.h"
#include "conn.h"
#include "gyro.h"

#pragma once

class Gauntlet
{
private:
    MultiFlex *flexSensors = NULL;
    char const* names[256] = {};
    Gyro gyro;
public:
    Gauntlet(){};
    Gauntlet(uint8_t thumb, uint8_t index, uint8_t middle, uint8_t ring, uint8_t little, uint8_t wrist, uint8_t accel);
    void begin();
    void loop();
    const char* getName(byte addr);
    char* formatSensorData(int addr, float x, float y);
    void callbackFn(float x, float y, int addr, int num);
};