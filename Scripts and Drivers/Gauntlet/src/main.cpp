#include <Arduino.h>
#include "gauntlet.h"
#include "conn.h"

Gauntlet gauntlet;

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    gauntlet = Gauntlet(); 
    gauntlet.addFlexSensor({"thu", 0x24, -175, -40, 0, 100});
    gauntlet.addFlexSensor({"ind", 0x19, -170, -360, 0, 100});
    gauntlet.addFlexSensor({"mid", 0x40, -100, -230, 0, 100});
    gauntlet.addFlexSensor({"wri", 0x2d, -32, 40, -66, 12});
    gauntlet.addFlexSensor({"elb", 0x33, 0, 100, 0, 100});
    Conn::begin("255.255.255.255", 1420); //port >1024?
}

void loop()
{
    gauntlet.loop();
    yield();
}
