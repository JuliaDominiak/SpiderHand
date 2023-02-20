#include <multiFlex.h>

MultiFlex::MultiFlex(int numFlex, uint8_t flexAdddresses[])
{
    this->numFlex = numFlex;
    this->flexSensors = (ADS *)malloc(sizeof(ADS) * numFlex);
    this->flexAdddresses = flexAdddresses;
}

void MultiFlex::begin()
{
    for (int i = 0; i < numFlex; ++i)
    {
        this->flexSensors[i] = ADS();
        if (!this->flexSensors[i].begin(flexAdddresses[i]))
        {
            Serial.printf("Error connecting to flex sensor addr:%x\n", flexAdddresses[i]);
            ESP.restart();
        }
        Serial.printf("Flex connected, addr:%x\n", flexAdddresses[i]);
    }
}

float MultiFlex::getX(int sensorNum)
{
    return flexSensors[sensorNum].getX();
}

float MultiFlex::getY(int sensorNum)
{
    return flexSensors[sensorNum].getY();
}

void MultiFlex::setCallbackFn(void callbackFn(float, float, int, int))
{
    this->callbackFn = callbackFn;
}

void MultiFlex::loop()
{
    if (callbackFn == NULL)
    {
        return;
    }
    for (int i = 0; i < numFlex; ++i)
    {
        if (!flexSensors[i].available())
        {
            continue;
        }
        callbackFn(flexSensors[i].getX(), flexSensors[i].getY(), flexAdddresses[i], i);
    }
}