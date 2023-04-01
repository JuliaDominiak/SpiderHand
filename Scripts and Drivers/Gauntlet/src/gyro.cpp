#include "gyro.h"

Gyro::Gyro(uint8_t addr){
    mpu = MPU6050(addr);
}

void Gyro::begin(){
    mpu.initialize();
    if (!mpu.testConnection()){
        Serial.println("MPU connection failed");
    }
    Serial.println("MPU connection success");
}

void Gyro::loop(){
    int16_t ax, ay, az;  // define accel as ax,ay,az
    int16_t gx, gy, gz;  // define gyro as gx,gy,gz
    mpu.getMotion6(&gy, &gx, &gz, &ay, &ax, &az);  // read measurements from device
    // ACHTUNG: I am done dealing with BS that comes with gyros so this code is stolen from previous version,
    // no I have no idea what is going on, and I don't intend on understanding it, but aparently IT WORKS???
    int16_t sensor=gy-570;
    int kat=90-sensor/182;
    kat=kat/3; //LOL
    kat=kat*3; //WHAT?
    Serial.printf("gyro %i",kat);
}