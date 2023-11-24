#include <Arduino.h>
#include "gauntlet.h"
#include "conn.h"

Gauntlet gauntlet;

// cppcheck-suppress unusedFunction
void setup()
{
    Serial.begin(115200);
    Wire.begin();
    gauntlet = Gauntlet(); 
    gauntlet.addFlexSensor(FlexSensor("thu", 0x24, -175, -40, 0, 100));
    gauntlet.addFlexSensor(FlexSensor("ind", 0x19, -170, -360, 0, 100));
    gauntlet.addFlexSensor(FlexSensor("mid", 0x40, -100, -230, 0, 100));
    gauntlet.addFlexSensor(FlexSensor("wri", 0x2d, -32, 40, -66, 12));
    gauntlet.addFlexSensor(FlexSensor("elb", 0x33, -2, 560, 0, 100));
    Conn::begin("255.255.255.255", 1420); //broadcast
}

// cppcheck-suppress unusedFunction
void loop()
{
    gauntlet.loop();
    yield();
}
