//
// Created by Mike van Es on 12-4-2021.
//

#pragma once


#include "FriendlyDelay.h"

enum Steps {FULL, HALF, QUARTER, EIGHT, SIXTEENTH};

class MotorDriver{
public:
    MotorDriver(Steps step, unsigned int leftRPM, unsigned int rightRPM);

    void SetStep(Steps step);
    void TurnLeftMotor();
    void TurnRightMotor();
    void SetDirection(int motorPin, byte dir);
    void SetRightMotorSpeed(unsigned int RPM );
    void SetLeftMotorSpeed(unsigned int RPM );

private:
    FriendlyDelay* LeftMotorTimer;
    FriendlyDelay* RightMotorTimer;
    int rightMotorRPM;
    int leftMotorRPM;
    double stepMode;
    void SetupPins();
    void SetInterrupt();

};