//
// Created by Mike van Es on 13/04/2021.
//

#pragma once
#include <Arduino.h>
#include "../Defines/AcceleroDefines.h"
#include <MPU9250_WE.h>

class AcceleroDriver {
public:
    AcceleroDriver();
    int GetAngle();
    bool SetupWire();

    static bool allow_read;

private:
    void SetInterrupt();

    float compFilter[1] = {0};
    MPU9250_WE myMPU9250;
    const int ALPHA = 0.5;
    int SUM, READINGS[WINDOW_SIZE], INDEX, AVERAGED;

};
