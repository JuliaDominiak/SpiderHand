#include "hand.h"

Hand::Hand(){

}

void Hand::addServo(std::string jointName, byte dimensionIndex, int servoAddress){
    std::map<std::string, int*> map;
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
        Serial.printf("setting %d to %f", servoarr[0], x);
        //pca.setPWM(servoarr[0], 0, x);
    }
    if (servoarr[1]!=-1){
        Serial.printf("setting %d to %f", servoarr[1], y);
        //pca.setPWM(servoarr[1], 0, y);
    }
}