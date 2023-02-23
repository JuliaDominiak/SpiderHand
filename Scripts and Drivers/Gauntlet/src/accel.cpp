#include "accel.h"

Accel::Accel(uint8_t addr){
    mpu = MPU6050(addr);
}

void Accel::begin(){
    mpu.initialize();
    if (!mpu.testConnection()){
        Serial.println("MPU connection failed");
    }
    Serial.println("MPU connection success");
}

void Accel::loop(){
    int16_t x,y,z;
    mpu.getRotation(&x,&y,&z);
    Serial.printf("acc %i, %i, %i", x, y, z);
}