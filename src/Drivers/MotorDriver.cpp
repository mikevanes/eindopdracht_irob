//
// Created by Mike van Es on 12-4-2021.
//

#include <Arduino.h>
#include "../Defines/MotorDefines.h"
#include "FriendlyDelay.h"
#include "MotorDriver.h"

MotorDriver::MotorDriver(Steps step, unsigned long RightMotorDelayUS, unsigned long LeftMotorDelayUS) {
    this->SetStep(step);

    this->SetDirection(LEFT_MOTOR_DIR, TURN_RIGHT);
    this->SetDirection(RIGHT_MOTOR_DIR, TURN_RIGHT);

    this->SetupPins();

    this->LeftMotorTimer = new FriendlyDelay(LeftMotorDelayUS);
    this->RightMotorTimer = new FriendlyDelay(RightMotorDelayUS);

}
void MotorDriver::SetupPins() {
    pinMode(LEFT_MOTOR_STEP, OUTPUT);
    pinMode(LEFT_MOTOR_DIR, OUTPUT);

    pinMode(RIGHT_MOTOR_STEP, OUTPUT);
    pinMode(RIGHT_MOTOR_DIR, OUTPUT);

    pinMode(LEFTMS1, OUTPUT);
    pinMode(LEFTMS2, OUTPUT);
    pinMode(LEFTMS3, OUTPUT);

    pinMode(RIGHTMS1, OUTPUT);
    pinMode(RIGHTMS2, OUTPUT);
    pinMode(RIGHTMS3, OUTPUT);



}

void MotorDriver::SetDirection(int motorPin, byte dir){
    digitalWrite(motorPin, dir);
}
void MotorDriver::SetLeftMotorSpeed(unsigned long delay ){
    this->LeftMotorTimer->SetDelay(delay);
}
void MotorDriver::SetRightMotorSpeed(unsigned long delay ){
    this->RightMotorTimer->SetDelay(delay);
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

void MotorDriver::SetStep(Steps step){
    switch(step) {
        case Steps::FULL:
            digitalWrite(LEFTMS1, LOW);
            digitalWrite(LEFTMS2, LOW);
            digitalWrite(LEFTMS3, LOW);
            digitalWrite(RIGHTMS1, LOW);
            digitalWrite(RIGHTMS2, LOW);
            digitalWrite(RIGHTMS3, LOW);

            break;
        case Steps::HALF:
            digitalWrite(LEFTMS1, HIGH);
            digitalWrite(LEFTMS2, LOW);
            digitalWrite(LEFTMS3, LOW);
            digitalWrite(RIGHTMS1, HIGH);
            digitalWrite(RIGHTMS2, LOW);
            digitalWrite(RIGHTMS3, LOW);

            break;
        case Steps::QUARTER:
            digitalWrite(LEFTMS1, LOW);
            digitalWrite(LEFTMS2, HIGH);
            digitalWrite(LEFTMS3, LOW);
            digitalWrite(RIGHTMS1, LOW);
            digitalWrite(RIGHTMS2, HIGH);
            digitalWrite(RIGHTMS3, LOW);

            break;
        case Steps::EIGHT:
            digitalWrite(LEFTMS1, HIGH);
            digitalWrite(LEFTMS2, HIGH);
            digitalWrite(LEFTMS3, LOW);
            digitalWrite(RIGHTMS1, HIGH);
            digitalWrite(RIGHTMS2, HIGH);
            digitalWrite(RIGHTMS3, LOW);

            break;
        case Steps::SIXTEENTH:
            digitalWrite(LEFTMS1, HIGH);
            digitalWrite(LEFTMS2, HIGH);
            digitalWrite(LEFTMS3, HIGH);
            digitalWrite(RIGHTMS1, HIGH);
            digitalWrite(RIGHTMS2, HIGH);
            digitalWrite(RIGHTMS3, HIGH);

            break;
    }
}



