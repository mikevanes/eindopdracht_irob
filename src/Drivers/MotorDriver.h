//
// Created by Mike van Es on 12-4-2021.
//

#pragma once


#include "FriendlyDelay.h"

enum Steps {FULL, HALF, QUARTER, EIGHT, SIXTEENTH};

class MotorDriver{
public:
    MotorDriver(Steps step, unsigned long delayUS);
    void SetupPins();
    void SetStep(Steps step);

    void TurnLeftMotor();
    void TurnRightMotor();

private:
    FriendlyDelay* LeftMotorTimer;
    FriendlyDelay* RightMotorTimer;

};