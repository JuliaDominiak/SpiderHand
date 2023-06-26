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

Gauntlet::Gauntlet()
{
    flexSensors = (FlexSensorData **)malloc(sizeof(FlexSensorData *) * 0);
}

char *Gauntlet::formatSensorData(char* name, float x, float y)
{
    char *buf = (char *)malloc(sizeof(char) * 18); // abc-179.12  -2.45\0
    sprintf(buf, "%s%7.2f%7.2f\0", name, x, y);
    return buf;
}

void Gauntlet::addFlexSensor(const FlexSensor sensor){
    numFlexSensors++;
    flexSensors = (FlexSensorData**)realloc(flexSensors, sizeof(FlexSensorData*)*numFlexSensors);
    if (flexSensors == NULL){
        Serial.println("Error allocating memory for flex sensors");
        ESP.restart();
    }
    flexSensors[numFlexSensors-1] = new FlexSensorData(sensor);
}

void Gauntlet::loop()
{
    for (int i = 0; i < numFlexSensors; i++)
    {
        if (!flexSensors[i]->sensor.isConnected() || !flexSensors[i]->sensor.available())
        {
            continue;
        }
        Conn::beginPacket();
        flexSensors[i]->x = flexSensors[i]->sensor.getX();
        flexSensors[i]->y = flexSensors[i]->sensor.getY();
        float xCal = map_Generic<float>(flexSensors[i]->x.get(), flexSensors[i]->minX, flexSensors[i]->maxX, 0, 100);
        float yCal = map_Generic<float>(flexSensors[i]->y.get(), flexSensors[i]->minY, flexSensors[i]->maxY, 0, 100);
        // serialCallbackFn(xCal, yCal, flexSensors[i]->servoAddress, i);
        char *buf = formatSensorData(flexSensors[i]->jointName, xCal, yCal);
        Serial.println(buf);
        //free(buf);
        Conn::write(buf, 17);
        free(buf);
        Conn::endPacket();
    }
}
