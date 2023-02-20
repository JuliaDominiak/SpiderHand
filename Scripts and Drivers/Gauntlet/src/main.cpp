#include <Arduino.h>
#include "multiFlex.h"

MultiFlex flexSensors(2, (uint8_t[]){0x12, 0x14});

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
    sprintf(buf, "%x|%c%6.2f|%c%6.2f\0", addr, xSign, x, ySign, y);
    return buf;
}

void callbackFn(float x, float y, int addr, int num)
{
    char *buf = formatSensorData(addr, x, y);
    Serial.println(buf);
    free(buf);
}

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    flexSensors.begin();
    flexSensors.setCallbackFn(callbackFn);
}

void loop()
{
    flexSensors.loop();
    yield();
}
