//
// Created by Mike van Es on 12-4-2021.
//

#pragma once


#include "FriendlyDelay.h"

enum Steps {FULL, HALF, QUARTER, EIGHT, SIXTEENTH};

class MotorDriver{
public:
    MotorDriver();


    void TurnLeftMotor();
    void TurnRightMotor();
    void SetDirection(int motorPin, byte dir);
    void SetRightMotorSpeed(unsigned int RPM );
    void SetLeftMotorSpeed(unsigned int RPM );
    void HaltMotor();
    void SetStep(Steps step);

private:
    FriendlyDelay* LeftMotorTimer;
    FriendlyDelay* RightMotorTimer;
    int rightMotorRPM, leftMotorRPM, stepMode;

    void SetupPins();


};