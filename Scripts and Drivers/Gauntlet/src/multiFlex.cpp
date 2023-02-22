#include <multiFlex.h>

MultiFlex::MultiFlex(int numFlex, uint8_t flexAdddresses[])
{
    this->numFlex = numFlex;
    this->flexSensors = (ADS *)malloc(sizeof(ADS) * numFlex);
    this->flexAdddresses = (uint8_t *)malloc(sizeof(uint8_t) * numFlex);
    memcpy(this->flexAdddresses, flexAdddresses, sizeof(uint8_t) * numFlex);
}

void MultiFlex::begin()
{
    for (int i = 0; i < numFlex; ++i)
    {
        this->flexSensors[i] = ADS();
        if (!this->flexSensors[i].begin(flexAdddresses[i]))
        {
            if (flexAdddresses[i] == 0xff)
            {
                continue;
            }
            Serial.printf("Error connecting to flex sensor addr:%x, id: %d\n", flexAdddresses[i], i);
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

void MultiFlex::setCallbackFn(std::function<void(float, float, int, int)> callbackFn)
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
        if (!flexSensors[i].isConnected() || !flexSensors[i].available())
        {
            continue;
        }
        callbackFn(flexSensors[i].getX(), flexSensors[i].getY(), flexAdddresses[i], i);
    }
}