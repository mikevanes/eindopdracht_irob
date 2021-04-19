//
// Created by Mike van Es on 15-4-2021.
//

#pragma once


class PIDcontroller {
public:
    PIDcontroller();
    float GetPID(float currentAngle, float elapsedTime);
private:
    float pid;
    float pidP;
    float pidI;
    float pidD;
    float error;
    float prevError;
};

