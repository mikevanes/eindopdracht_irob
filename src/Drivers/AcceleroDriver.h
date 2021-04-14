//
// Created by Mike van Es on 13/04/2021.
//

#pragma once
#include <Arduino.h>
#include "../Defines/AcceleroDefines.h"

class AcceleroDriver {
public:
    AcceleroDriver();
    int GetAngle();
    static bool allow_read;
private:
    void SetupWire();
    void WireTransmission();
    void WireRead();
    void SetInterrupt();

    int INDEX, SUM, AVG, READINGS[WINDOW_SIZE], y;
    int16_t AcX,AcY,AcZ;

};
