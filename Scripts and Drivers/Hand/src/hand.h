#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <map>

#define DIM_NUM 2

#pragma once

class Hand{
    private:
    Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver();
    std::map<std::string,int*> jointToServo;
    public:
    Hand();
    void addServo(std::string jointName, byte dimensionIndex, int servoAddress);
    void parseCommand(std::string cmd);
};