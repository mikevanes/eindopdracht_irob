//
// Created by Mike van Es on 15-4-2021.
//

#include "PIDcontroller.h"
#include "../Defines/PIDDefines.h"
#include <Arduino.h>

PIDcontroller::PIDcontroller() {
    this->cumError = 0;
    this->prevError = 0;
    this->error = 0;
    this->rateError = 0;
}

double PIDcontroller::GetPID(int currentAngle, float elapsedTime) {
    this->error = DESIRED_ANGLE - currentAngle;
    double P = KP * this->error;

    this->cumError = this->cumError + this->error * elapsedTime;
    double I = KI * this->cumError;

    this->rateError = (this->error - this->prevError);
    double D = KD * this->rateError;

    this->prevError = this->error;

    double PID = P + I + D;

    return PID;
}