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

char *Gauntlet::formatSensorData(std::string name, float x, float y)
{
    char *buf = (char *)malloc(sizeof(char) * 18); // abc-179.12  -2.45\0
    sprintf(buf, "%s%7.2f%7.2f\0", name, x, y);
    return buf;
}

void Gauntlet::addFlexSensor(FlexSensor sensor){
    numFlexSensors++;
    flexSensors = (FlexSensorData*)realloc(flexSensors, sizeof(FlexSensorData)*numFlexSensors);
    flexSensors[numFlexSensors-1] = FlexSensorData(sensor);
}

void Gauntlet::loop()
{
    for (int i = 0; i < numFlexSensors; i++)
    {
        Conn::beginPacket();
        float x = flexSensors[i].sensor.getX();
        float y = flexSensors[i].sensor.getY();
        float xCal = map_Generic<float>(x, flexSensors[i].minX, flexSensors[i].maxX, 0, 100);
        float yCal = map_Generic<float>(y, flexSensors[i].minY, flexSensors[i].maxY, 0, 100);
        char *buf = formatSensorData(flexSensors[i].jointName, xCal, yCal);
        Conn::write(buf, 17);
        free(buf);
        Conn::endPacket();
    }
}
