//
// Created by Mike van Es on 15-4-2021.
//

#include <HardwareSerial.h>
#include "PIDcontroller.h"
#include "../Defines/PIDDefines.h"
#include <Arduino.h>

PIDcontroller::PIDcontroller() {
    this->pidD = 0;
    this->pidI = 0;
    this->pidP = 0;
}
float PIDcontroller::GetPID(float currentAngle, float elapsedTime) {
    this->error = currentAngle - DESIRED_ANGLE;

    this->pidP = KP*error;

    this->pidI = this->pidI+(KI*error);

    this->pidD = KD*((this->error - this->prevError)/elapsedTime);
//    if(isnan(this->pidD)){
//        this->pidD = 0;
//    }

    this->pid = this->pidP + this->pidD;
    this->prevError = error;

    return abs(this->pid);
}