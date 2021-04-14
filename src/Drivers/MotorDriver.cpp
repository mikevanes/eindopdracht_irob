//
// Created by Mike van Es on 12-4-2021.
//

#include <Arduino.h>
#include "../Defines/MotorDefines.h"
#include "FriendlyDelay.h"
#include "MotorDriver.h"


MotorDriver::MotorDriver(Steps step, unsigned int leftRPM, unsigned int rightRPM) {
    this->SetupPins();
    this->SetStep(step);

    this->SetDirection(LEFT_MOTOR_DIR, TURN_RIGHT);
    this->SetDirection(RIGHT_MOTOR_DIR, TURN_RIGHT);

    //RPM to US
    unsigned long delay = 1000000 / ( leftRPM / ( (this->stepMode/360) * 60) );
    this->LeftMotorTimer = new FriendlyDelay(delay);

    delay = 1000000 / ( rightRPM / ( (this->stepMode/360) * 60) );
    this->RightMotorTimer = new FriendlyDelay(delay);
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
void MotorDriver::SetLeftMotorSpeed(unsigned int RPM ){
    this->leftMotorRPM  = RPM;

    //RPM to US
    unsigned long delay = 1000000 / ( this->leftMotorRPM / ( (this->stepMode/360) * 60) );

    this->LeftMotorTimer->SetDelay(delay);
}
void MotorDriver::SetRightMotorSpeed(unsigned int RPM ){
    this->rightMotorRPM  = RPM;

    //RPM to US
    unsigned long delay = 1000000 / ( this->rightMotorRPM / ( (this->stepMode/360) * 60) );

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
            this->stepMode = 1.8;

//            digitalWrite(LEFTMS1, LOW);
//            digitalWrite(LEFTMS2, LOW);
//            digitalWrite(LEFTMS3, LOW);
//            digitalWrite(RIGHTMS1, LOW);
//            digitalWrite(RIGHTMS2, LOW);
//            digitalWrite(RIGHTMS3, LOW);

            break;
        case Steps::HALF:
            this->stepMode = 0.9;

//            digitalWrite(LEFTMS1, HIGH);
//            digitalWrite(LEFTMS2, LOW);
//            digitalWrite(LEFTMS3, LOW);
//            digitalWrite(RIGHTMS1, HIGH);
//            digitalWrite(RIGHTMS2, LOW);
//            digitalWrite(RIGHTMS3, LOW);

            break;
        case Steps::QUARTER:
            this->stepMode = 0.45;

//            digitalWrite(LEFTMS1, LOW);
//            digitalWrite(LEFTMS2, HIGH);
//            digitalWrite(LEFTMS3, LOW);
//            digitalWrite(RIGHTMS1, LOW);
//            digitalWrite(RIGHTMS2, HIGH);
//            digitalWrite(RIGHTMS3, LOW);

            break;
        case Steps::EIGHT:
            this->stepMode = 0.225;

//            digitalWrite(LEFTMS1, HIGH);
//            digitalWrite(LEFTMS2, HIGH);
//            digitalWrite(LEFTMS3, LOW);
//            digitalWrite(RIGHTMS1, HIGH);
//            digitalWrite(RIGHTMS2, HIGH);
//            digitalWrite(RIGHTMS3, LOW);

            break;
        case Steps::SIXTEENTH:
            this->stepMode = 0.112;

//            digitalWrite(LEFTMS1, HIGH);
//            digitalWrite(LEFTMS2, HIGH);
//            digitalWrite(LEFTMS3, HIGH);
//            digitalWrite(RIGHTMS1, HIGH);
//            digitalWrite(RIGHTMS2, HIGH);
//            digitalWrite(RIGHTMS3, HIGH);

            break;
    }
}

void MotorDriver::SetInterrupt(){
    cli(); // stop interrupts
    TCCR0A = 0; // set entire TCCR0A register to 0
    TCCR0B = 0; // same for TCCR0B
    TCNT0  = 0; // initialize counter value to 0
    // set compare match register for 2000 Hz increments
    OCR0A = 124; // = 16000000 / (64 * 2000) - 1 (must be <256)
    // turn on CTC mode
    TCCR0B |= (1 << WGM01);
    // Set CS02, CS01 and CS00 bits for 64 prescaler
    TCCR0B |= (0 << CS02) | (1 << CS01) | (1 << CS00);
    // enable timer compare interrupt
    TIMSK0 |= (1 << OCIE0A);
    sei(); // allow interrupts
}

ISR(TIMER0_COMPA_vect){
    digitalWrite(RIGHT_MOTOR_STEP, !digitalRead(RIGHT_MOTOR_STEP) );
}



