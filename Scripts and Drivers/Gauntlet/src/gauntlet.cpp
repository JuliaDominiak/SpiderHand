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
    char *buf = Gauntlet::formatSensorData(addr, x, y);
    Conn::write(buf, 17);
    Conn::write("\n", 1);
    free(buf);
}

Gauntlet::Gauntlet(uint8_t thumb, uint8_t index, uint8_t middle, uint8_t ring, uint8_t little, uint8_t wrist, uint8_t accel)
{
    uint8_t addr[] = {thumb, index, middle, ring, little, wrist};
    flexSensors = new MultiFlex(6, addr);
    this->accel = Accel(accel);
    for (int i = 0; i < 256; i++)
    {
        names[i] = "non";
    }
    names[thumb] = "thu";
    names[index] = "ind";
    names[middle] = "mid";
    names[ring] = "rin";
    names[little] = "lit";
    names[wrist] = "wri";
}

void Gauntlet::begin()
{
    accel.begin();
    flexSensors->begin();
    flexSensors->setCallbackFn([this](float x, float y, int addr, int num){callbackFn(x, y, addr, num);}); //yeah ugly.... but it passes this.callbackFn to setCallbackFn, deal with it...
}

void Gauntlet::loop()
{
    Conn::beginPacket();
    flexSensors->loop();
    accel.loop();
    Conn::endPacket();
}

const char *Gauntlet::getName(byte addr)
{
    return names[addr];
}