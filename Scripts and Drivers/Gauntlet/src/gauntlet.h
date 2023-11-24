//#include "multiFlex.h"
#include "conn.h"
#include "gyro.h"
#include "utils.h"
#include "SparkFun_Displacement_Sensor_Arduino_Library.h"
#include "filters.h"
#include <map>

#ifndef FILTER_EPS
#define FILTER_EPS 5
#endif

// #ifndef EPSILON
// #define EPSILON 2
// #endif

#pragma once

struct FlexSensor{
    char jointName[4];
    int servoAddress;
    float minX;
    float maxX;
    float minY;
    float maxY;
    FlexSensor(const char* name, int addr, float minx, float maxx, float miny, float maxy){
        memcpy(jointName, name, 4);
        servoAddress = addr;
        minX = minx;
        maxX = maxx;
        minY = miny;
        maxY = maxy;
    }
};

struct FlexSensorData {
    char jointName[4];
    int servoAddress;
    float minX;
    float maxX;
    float minY;
    float maxY;
    ADS sensor;
    FastFiltered<float> x;
    FastFiltered<float> y;
    float previousX = MAXFLOAT;
    float previousY = MAXFLOAT;

    explicit FlexSensorData(const FlexSensor definition){
        memcpy(jointName, definition.jointName, 4);
        servoAddress = definition.servoAddress;
        minX = definition.minX;
        maxX = definition.maxX;
        minY = definition.minY;
        maxY = definition.maxY;
        sensor = ADS();
        if (!sensor.begin(servoAddress))
        {
            Serial.printf("Error connecting to flex sensor addr:%x\n", servoAddress);
            ESP.restart();
        }
        Serial.printf("Flex connected, addr:%x\n", servoAddress);  
        x = FastFiltered<float>(FILTER_EPS);
        y = FastFiltered<float>(FILTER_EPS); 
    }
};

class Gauntlet
{
private:
    FlexSensorData **flexSensors; 
    uint8_t numFlexSensors = 0;
    Gyro gyro;
    char* formatSensorData(char* name, float x, float y);
public:
    Gauntlet();
    void addFlexSensor(FlexSensor sensor);
    void loop();
};