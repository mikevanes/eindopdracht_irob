//
// Created by Mike van Es on 12-4-2021.
//
#pragma once

class FriendlyDelay{
public:
    signed long delayUS;
    unsigned long TimeNow;

    FriendlyDelay(unsigned long delayUS);

    void SetDelay(unsigned long delayUS);

    bool CheckTime();


};

