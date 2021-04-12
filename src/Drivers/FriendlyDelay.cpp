//
// Created by Mike van Es on 12-4-2021.
//

#include <Arduino.h>
#include "FriendlyDelay.h"

FriendlyDelay::FriendlyDelay(unsigned long delayUS){
    this->delayUS = delayUS;
    this->TimeNow = micros();
}

void FriendlyDelay::SetDelay(unsigned long delayUS){
    this->delayUS = delayUS;
}

bool FriendlyDelay::CheckTime(){
    if( (micros() - this->TimeNow) >= this->delayUS ){
        this->TimeNow = micros();
        return true;
    }

    return false;
}
