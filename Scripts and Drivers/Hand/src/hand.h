#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <map>
#include "utils.h"

#define DIM_NUM 2

#pragma once

class Hand{
    private:
    Adafruit_PWMServoDriver pca;
    std::map<std::string,int*> jointToServo;
    std::map<int,int*> servoToRange;
    public:
    Hand();
    void addServo(std::string jointName, byte dimensionIndex, int servoAddress, uint16_t min, uint16_t max);
    void parseCommand(std::string cmd);
};