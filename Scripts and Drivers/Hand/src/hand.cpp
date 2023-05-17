#include "hand.h"

Hand::Hand(){
    pca = Adafruit_PWMServoDriver();
    pca.begin();
    pca.setPWMFreq(50);
}

void Hand::addServo(std::string jointName, byte dimensionIndex, int servoAddress, uint16_t min, uint16_t max){
    auto servoarrItr = jointToServo.find(jointName);
    int* servoarr;
    if (servoarrItr == jointToServo.end()){
        servoarr = new int[DIM_NUM];
        jointToServo.insert({jointName, servoarr});
        std::fill_n(servoarr, DIM_NUM, -1);
    }
    else{
        servoarr = servoarrItr->second;
    }
    servoarr[dimensionIndex] = servoAddress;
    int* range = new int[2]{min,max};
    servoToRange[servoAddress] = range;
}
void Hand::parseCommand(std::string cmd){
    std::string jointName = cmd.substr(0,3);
    float x = std::stof(cmd.substr(3,7));
    float y = std::stof(cmd.substr(10,7));
    Serial.printf("parsed: %s, %f, %f\n", jointName.c_str(),x,y);

    auto servoarrItr = jointToServo.find(jointName);
    int* servoarr;
    if (servoarrItr == jointToServo.end()){
        Serial.printf("Unknown joint %s\n", jointName.c_str());
        return;
    }else{
        servoarr = servoarrItr->second;
    }

    if (servoarr[0]!=-1){
        int* range = servoToRange.at(servoarr[0]);
        float pwm = map_Generic(x, 0.0f, 100.0f, (float)range[0], (float)range[1]);
        Serial.printf("setting %d to %f%, val:%f", servoarr[0], x, pwm);
        pca.setPWM(servoarr[0], 0, pwm);
    }
    if (servoarr[1]!=-1){
        int* range = servoToRange.at(servoarr[1]);
        float pwm = map_Generic(y, 0.0f, 100.0f, (float)range[0], (float)range[1]);
        Serial.printf("setting %d to %f%, val:%f", servoarr[1], y, pwm);
        pca.setPWM(servoarr[1], 0, pwm);
    }
}