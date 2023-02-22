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

void callbackFn(float x, float y, int addr, int num)
{
    char *buf = formatSensorData(addr, x, y);
    Serial.println(buf);
    free(buf);
}

void wifiCallbackFn(float x, float y, int addr, int num){
    char *buf = formatSensorData(addr, x, y);
    Conn::write(buf, 20);
    Conn::write("\n",1);
    free(buf);
}

Gauntlet::Gauntlet(uint8_t thumb, uint8_t index, uint8_t middle, uint8_t ring, uint8_t little, uint8_t wrist)
{
    uint8_t addr[] = {thumb, index, middle, ring, little, wrist};
    flexSensors = new MultiFlex(6, addr);
}

void Gauntlet::begin()
{
    flexSensors->begin();
    flexSensors->setCallbackFn(wifiCallbackFn);
}

void Gauntlet::loop()
{
    Conn::beginPacket();
    flexSensors->loop();
    Conn::endPacket();
}