#include "multiFlex.h"
#include "conn.h"

#pragma once

class Gauntlet
{
private:
    MultiFlex *flexSensors = NULL;

public:
    Gauntlet(){};
    Gauntlet(uint8_t thumb, uint8_t index, uint8_t middle, uint8_t ring, uint8_t little, uint8_t wrist);
    void begin();
    void loop();
};