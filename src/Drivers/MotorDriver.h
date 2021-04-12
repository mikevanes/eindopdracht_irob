//
// Created by Mike van Es on 12-4-2021.
//

#pragma once


#include "FriendlyDelay.h"

enum Steps {FULL, HALF, QUARTER, EIGHT, SIXTEENTH};

class MotorDriver{
public:
    MotorDriver(Steps step, unsigned long RightMotorDelayUS, unsigned long LeftMotorDelayUS);

    void SetStep(Steps step);
    void TurnLeftMotor();
    void TurnRightMotor();
    void SetDirection(int motorPin, byte dir);
    void SetRightMotorSpeed(unsigned long delay );
    void SetLeftMotorSpeed(unsigned long delay );

private:
    FriendlyDelay* LeftMotorTimer;
    FriendlyDelay* RightMotorTimer;

    void SetupPins();

};