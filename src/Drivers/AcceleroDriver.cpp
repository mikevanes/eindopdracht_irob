//
// Created by Mike van Es on 13/04/2021.
//

#include "AcceleroDriver.h"
#include "../Defines/AcceleroDefines.h"
#include<Wire.h>
#include <Arduino.h>

AcceleroDriver::AcceleroDriver() {
    this->SetupWire();
    this->INDEX = 0;
    this->SUM = 0;
    this->AVG = 0;

    AcceleroDriver::SetInterrupt();
}

int AcceleroDriver::GetAngle() {
    if(!AcceleroDriver::allow_read) return this->AVG;

    AcceleroDriver::allow_read = false;

    this->WireTransmission();
    this->WireRead();

    this->y = atan2(this->AcX , this->AcZ) * -180.0 / PI;

    this->SUM = this->SUM - this->READINGS[INDEX];
    this->READINGS[this->INDEX] = this->y;
    this->SUM = this->SUM + this->y;
    this->INDEX = (this->INDEX + 1) % WINDOW_SIZE;

    this->AVG = this->SUM / WINDOW_SIZE;

    return this->AVG;
}
void AcceleroDriver::SetupWire() {
    Wire.begin();
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
}
void AcceleroDriver::WireTransmission() {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR,6,true);
}
void AcceleroDriver::WireRead() {
    this->AcX=Wire.read()<<8|Wire.read();
    this->AcY=Wire.read()<<8|Wire.read();
    this->AcZ=Wire.read()<<8|Wire.read();
}

void AcceleroDriver::SetInterrupt() {
    // TIMER 1 for interrupt frequency 4 Hz:
    cli(); // stop interrupts
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1  = 0; // initialize counter value to 0
    // set compare match register for 4 Hz increments
    OCR1A = 62499; // = 16000000 / (64 * 4) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS12, CS11 and CS10 bits for 64 prescaler
    TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    sei(); // allow interrupts

}

ISR(TIMER1_COMPA_vect){
    AcceleroDriver::allow_read = true;
}

bool AcceleroDriver::allow_read = false;