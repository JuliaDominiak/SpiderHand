//#include "multiFlex.h"
#include "conn.h"
#include "gyro.h"
#include "utils.h"
#include "SparkFun_Displacement_Sensor_Arduino_Library.h"
#include <map>

#pragma once

struct FlexSensor{
    std::string jointName;
    int servoAddress;
    float minX;
    float maxX;
    float minY;
    float maxY;
};

class Gauntlet
{
private:
    struct FlexSensorData {
        std::string jointName;
        int servoAddress;
        float minX;
        float maxX;
        float minY;
        float maxY;
        ADS sensor;
        FlexSensorData(FlexSensor definition){
            jointName = definition.jointName;
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
        }
    };
    FlexSensorData *flexSensors; 
    uint8_t numFlexSensors = 0;
    Gyro gyro;
    char* formatSensorData(std::string name, float x, float y);
public:
    Gauntlet(){};
    void addFlexSensor(FlexSensor sensor);
    void loop();
};