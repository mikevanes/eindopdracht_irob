//
// Created by Mike van Es on 12-4-2021.
//

#include <Arduino.h>
#include "../Defines/MotorDefines.h"
#include "FriendlyDelay.h"
#include "MotorDriver.h"


MotorDriver::MotorDriver() {
    this->SetupPins();
    this->LeftMotorTimer = new FriendlyDelay(MAX_SPEED);
    this->RightMotorTimer = new FriendlyDelay(MAX_SPEED);

    this->SetStep(Steps::EIGHT);
}

void MotorDriver::SetupPins() {
    pinMode(LEFT_MOTOR_STEP, OUTPUT);
    pinMode(LEFT_MOTOR_DIR, OUTPUT);

    pinMode(RIGHT_MOTOR_STEP, OUTPUT);
    pinMode(RIGHT_MOTOR_DIR, OUTPUT);

    pinMode(MS1, OUTPUT);
    pinMode(MS2, OUTPUT);
    pinMode(MS3, OUTPUT);
}

void MotorDriver::SetDirection(int motorPin, byte dir){
    digitalWrite(motorPin, dir);
}
void MotorDriver::SetLeftMotorSpeed(unsigned int RPM ){
    this->leftMotorRPM  = RPM;

    this->LeftMotorTimer->SetDelay(RPM);
}
void MotorDriver::SetRightMotorSpeed(unsigned int RPM ){
    this->rightMotorRPM  = RPM;

    this->RightMotorTimer->SetDelay(RPM);
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

void MotorDriver::HaltMotor(){
    digitalWrite(RIGHT_MOTOR_STEP, 0x00);
    digitalWrite(LEFT_MOTOR_STEP, 0x00);
}

void MotorDriver::SetStep(Steps step){
    switch(step) {
        case Steps::FULL:
            this->stepMode = 0;

            digitalWrite(MS1, LOW);
            digitalWrite(MS2, LOW);
            digitalWrite(MS3, LOW);

            break;
        case Steps::HALF:
            this->stepMode = 1;

            digitalWrite(MS1, HIGH);
            digitalWrite(MS2, LOW);
            digitalWrite(MS3, LOW);

            break;
        case Steps::QUARTER:
            this->stepMode = 2;

            digitalWrite(MS1, LOW);
            digitalWrite(MS2, HIGH);
            digitalWrite(MS3, LOW);

            break;
        case Steps::EIGHT:
            this->stepMode = 3;

            digitalWrite(MS1, HIGH);
            digitalWrite(MS2, HIGH);
            digitalWrite(MS3, LOW);

            break;
        case Steps::SIXTEENTH:
            this->stepMode = 4;

            digitalWrite(MS1, HIGH);
            digitalWrite(MS2, HIGH);
            digitalWrite(MS3, HIGH);

            break;
    }
}



