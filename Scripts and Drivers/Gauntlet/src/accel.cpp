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
    mpu.dmpInitialize();
    mpu.setXGyroOffset(1);
    mpu.setYGyroOffset(5);
    mpu.setZGyroOffset(5);
    mpu.setXAccelOffset(-3822);
    mpu.setYAccelOffset(1545);
    mpu.setZAccelOffset(886);
    mpu.setDMPEnabled(true);
}

void Accel::loop(){
    if (!mpu.dmpGetCurrentFIFOPacket(fifoBuffer)){
        return;
    }
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetEuler(euler, &q);
    Serial.print("euler\t");
    Serial.print(euler[0] * 180/M_PI);
    Serial.print("\t");
    Serial.print(euler[1] * 180/M_PI);
    Serial.print("\t");
    Serial.println(euler[2] * 180/M_PI);
}