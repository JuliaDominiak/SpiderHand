#include "multiFlex.h"
#include "conn.h"
#include "gyro.h"
#include "utils.h"

#pragma once

class Gauntlet
{
private:
    MultiFlex *flexSensors = NULL;
    uint8_t addrToIdx[256] = {};
    char const* names[256] = {};
    Gyro gyro;
    float flexCalibrationData[7][2][2]={
        {{0,100},{0,100}},
        {{0,100},{0,100}},
        {{0,100},{0,100}},
        {{0,100},{0,100}},
        {{0,100},{0,100}},
        {{0,100},{0,100}},
        {{0,100},{0,100}}}; //7 flex sensors 2 axis 2 values (min max)

public:
    Gauntlet(){};
    Gauntlet(uint8_t thumb, uint8_t index, uint8_t middle, uint8_t ring, uint8_t little, uint8_t wrist, uint8_t elbow, uint8_t accel);
    void setCalibration(float thumbMin, float thumbMax,
                        float indexMin, float indexMax,
                        float middleMin, float middleMax,
                        float ringMin, float ringMax,
                        float littleMin, float littleMax,
                        float wristMinX, float wristMaxX,
                        float wristMinY, float wristMaxY);
    void begin();
    void loop();
    const char* getName(byte addr);
    char* formatSensorData(int addr, float x, float y);
    void callbackFn(float x, float y, int addr, int num);
};