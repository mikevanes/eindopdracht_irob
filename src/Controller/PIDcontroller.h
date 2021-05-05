//
// Created by Mike van Es on 15-4-2021.
//

#pragma once


class PIDcontroller {
public:
    PIDcontroller();
    double GetPID(int currentAngle, float elapsedTime);
private:
    double error, prevError, cumError, rateError;
    bool capped;
};

