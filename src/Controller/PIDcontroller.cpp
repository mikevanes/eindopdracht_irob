//
// Created by Mike van Es on 15-4-2021.
//

#include <HardwareSerial.h>
#include "PIDcontroller.h"
#include "../Defines/PIDDefines.h"
#include "../Defines/MotorDefines.h"
#include <Arduino.h>

PIDcontroller::PIDcontroller() {
    this->cumError = 0;
    this->prevError = 0;
    this->error = 0;
    this->rateError = 0;
}

double PIDcontroller::GetPID(int currentAngle, float elapsedTime) {
    this->error = DESIRED_ANGLE - currentAngle;

    this->cumError = this->cumError + this->error;
//    double P = KP * this->error;
    double I = KI * this->cumError;

    if(I >= MAX_SPEED){
        I = MAX_SPEED - MIN_SPEED;
    }

    if(I <= MAX_SPEED * -1){
        I = (MAX_SPEED - MIN_SPEED) *-1;
    }

    if(currentAngle == 0){
        this->cumError = 0;
    }

    this->rateError = (this->error - this->prevError);

    this->prevError = this->error;

    double PID = KP * this->error + I + KD * this->rateError;

    return PID;
}