#include "hand.h"

Hand::Hand(){
    pca = Adafruit_PWMServoDriver();
    pca.begin();
    pca.setPWMFreq(50);
}

void Hand::addServo(std::string jointName, byte dimensionIndex, int servoAddress, uint16_t min, uint16_t max){
    auto servoarrItr = jointToServo.find(jointName);
    int* servoarr;
    if (servoarrItr == jointToServo.end()){ //if throughout the whole map no such joint has been found
        servoarr = new int[DIM_NUM]; //create a new array of size DIM_NUM for each servo
        jointToServo.insert({jointName, servoarr}); //insert the joint name and the array into the map
        std::fill_n(servoarr, DIM_NUM, -1); //we set all values of servoarr to -1
    }
    else{
        servoarr = servoarrItr->second; //if the joint has been found, we get the array from the map
    }
    servoarr[dimensionIndex] = servoAddress; //we set the servo address at the axis index
    int* range = new int[2]{min,max}; //we create an array with minimal and maximal servo position
    servoToRange[servoAddress] = range;
}
void Hand::parseCommand(std::string cmd){
    std::string jointName = cmd.substr(0,3); //the first 3 chars was the name of the joint
    float x = std::stof(cmd.substr(3,7)); //the next 7 chars was the value on the x axis -- we change them to float
    float y = std::stof(cmd.substr(10,7)); //the next 7 chars was the value on the y axis -- we change them to float
    
    Serial.printf("parsed: %s, %f, %f\n", jointName.c_str(),x,y);

    x = clamp_Generic<float>(x, 0, 100); //if someone sent a value outside of the range, we clamp it to the range
    y = clamp_Generic<float>(y, 0, 100);

    auto servoarrItr = jointToServo.find(jointName); //we search for the joint in the map
    int* servoarr;
    if (servoarrItr == jointToServo.end()){
        Serial.printf("Unknown joint %s\n", jointName.c_str());
        return;
    }else{
        servoarr = servoarrItr->second; //if the joint has been found, we get the array from the map
    }

    if (servoarr[0]!=-1){ //if the servo for x axis has not been defined, we skip it
        int* range = servoToRange.at(servoarr[0]);
        float pwm = map_Generic(x, 0.0f, 100.0f, (float)range[0], (float)range[1]); //we map servos' position to range (0,100) ->(min,max)
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