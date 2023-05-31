#include "gauntlet.h"

char *formatSensorData(int addr, float x, float y)
{
    char *buf = (char *)malloc(sizeof(char) * 21); // 0xff|-179.12|-  2.45\0
    char xSign = ' ';
    char ySign = ' ';
    if (x < 0)
    {
        xSign = '-';
        x *= -1;
    }
    if (y < 0)
    {
        ySign = '-';
        y *= -1;
    }
    sprintf(buf, "0x%x|%c%6.2f|%c%6.2f\0", addr, xSign, x, ySign, y);
    return buf;
}

void serialCallbackFn(float x, float y, int addr, int num)
{
    char *buf = formatSensorData(addr, x, y);
    Serial.println(buf);
    free(buf);
}

char *Gauntlet::formatSensorData(int addr, float x, float y)
{
    char *buf = (char *)malloc(sizeof(char) * 18); // abc-179.12  -2.45\0
    sprintf(buf, "%s%7.2f%7.2f\0", getName(addr), x, y);
    return buf;
}

void Gauntlet::callbackFn(float x, float y, int addr, int num)
{
    Conn::beginPacket();
    uint8_t idx = addrToIdx[addr];
    float xCal = map_Generic<float>(x, flexCalibrationData[idx][0][0], flexCalibrationData[idx][0][1], 0, 100);
    float yCal = map_Generic<float>(y, flexCalibrationData[idx][1][0], flexCalibrationData[idx][1][1], 0, 100);
    char *buf = Gauntlet::formatSensorData(addr, xCal, yCal);
    Conn::write(buf, 17);
    //Conn::write("\n", 1);
    free(buf);
    Conn::endPacket();
}

Gauntlet::Gauntlet(uint8_t thumb, uint8_t index, uint8_t middle, uint8_t ring, uint8_t little, uint8_t wrist, uint8_t gyro)
{
    uint8_t addr[] = {thumb, index, middle, ring, little, wrist};
    flexSensors = new MultiFlex(6, addr);
    //this->gyro = Gyro(gyro);
    for (int i = 0; i < 256; i++)
    {
        names[i] = "non";
        addrToIdx[i] = 255;
    }
    addrToIdx[thumb] = 0;
    addrToIdx[index] = 1;
    addrToIdx[middle] = 2;
    addrToIdx[ring] = 3;
    addrToIdx[little] = 4;
    addrToIdx[wrist] = 5;
    names[addrToIdx[thumb]]  = "thu";
    names[addrToIdx[index]]  = "ind";
    names[addrToIdx[middle]] = "mid";
    names[addrToIdx[ring]]   = "rin";
    names[addrToIdx[little]] = "lit";
    names[addrToIdx[wrist]]  = "wri";
}

void Gauntlet::setCalibration(float thumbMin,  float thumbMax,
                              float indexMin,  float indexMax,
                              float middleMin, float middleMax,
                              float ringMin,   float ringMax,
                              float littleMin, float littleMax,
                              float wristMinX, float wristMaxX,
                              float wristMinY, float wristMaxY){
    flexCalibrationData[0][0][0]=thumbMin;
    flexCalibrationData[0][0][1]=thumbMax;
    flexCalibrationData[0][1][0]=thumbMin;
    flexCalibrationData[0][1][1]=thumbMax;
    flexCalibrationData[1][0][0]=indexMin;
    flexCalibrationData[1][0][1]=indexMax;
    flexCalibrationData[1][1][0]=indexMin;
    flexCalibrationData[1][1][1]=indexMax;
    flexCalibrationData[2][0][0]=middleMin;
    flexCalibrationData[2][0][1]=middleMax;
    flexCalibrationData[2][1][0]=middleMin;
    flexCalibrationData[2][1][1]=middleMax;
    flexCalibrationData[3][0][0]=ringMin;
    flexCalibrationData[3][0][1]=ringMax;
    flexCalibrationData[3][1][0]=ringMin;
    flexCalibrationData[3][1][1]=ringMax;
    flexCalibrationData[4][0][0]=littleMin;
    flexCalibrationData[4][0][1]=littleMax;
    flexCalibrationData[4][1][0]=littleMin;
    flexCalibrationData[4][1][1]=littleMax;
    flexCalibrationData[5][0][0]=wristMinX;
    flexCalibrationData[5][0][1]=wristMaxX;
    flexCalibrationData[5][1][0]=wristMinY;
    flexCalibrationData[5][1][1]=wristMaxY;
}

void Gauntlet::begin()
{
    //gyro.begin();
    flexSensors->begin();
    flexSensors->setCallbackFn([this](float x, float y, int addr, int num){callbackFn(x, y, addr, num);}); //yeah ugly.... but it passes this.callbackFn to setCallbackFn, deal with it...
}

void Gauntlet::loop()
{
    flexSensors->loop();
    //gyro.loop();
}

const char *Gauntlet::getName(byte addr)
{
    return names[addrToIdx[addr]];
}