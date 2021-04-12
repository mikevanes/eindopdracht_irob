//
// Created by Mike van Es on 12-4-2021.
//

#include <Arduino.h>
#include "../Defines/MotorDefines.h"
#include "FriendlyDelay.h"
#include "MotorDriver.h"

MotorDriver::MotorDriver(Steps step, unsigned long delayUS) {
    SetStep(step);

    this->LeftMotorTimer = new FriendlyDelay(delayUS);
    this->RightMotorTimer = new FriendlyDelay(delayUS);

}
void MotorDriver::SetupPins() {
    pinMode(LEFT_MOTOR_STEP, OUTPUT);
    pinMode(LEFT_MOTOR_DIR, OUTPUT);

    pinMode(RIGHT_MOTOR_STEP, OUTPUT);
    pinMode(RIGHT_MOTOR_DIR, OUTPUT);

    pinMode(MS1, OUTPUT);


    digitalWrite(RIGHT_MOTOR_DIR, HIGH);
    digitalWrite(LEFT_MOTOR_DIR, HIGH);

}
void MotorDriver::SetStep(Steps step){
    switch(step) {
        case Steps::FULL:
//            digitalWrite(MS1, LOW);
            break;
        case Steps::HALF:
            digitalWrite(MS1, HIGH);
            // code block
            break;
        case Steps::QUARTER:
            // code block
            break;
        case Steps::EIGHT:
            // code block
            break;
        case Steps::SIXTEENTH:
            // code block
            break;
    }
}

void MotorDriver::TurnLeftMotor() {
    if(this->LeftMotorTimer->CheckTime()){
        digitalWrite(LEFT_MOTOR_STEP, !digitalRead(LEFT_MOTOR_STEP) );
    }
}


void MotorDriver::TurnRightMotor() {
    if(this->RightMotorTimer->CheckTime()){
        digitalWrite(RIGHT_MOTOR_STEP, !digitalRead(RIGHT_MOTOR_STEP) );
    }
}



