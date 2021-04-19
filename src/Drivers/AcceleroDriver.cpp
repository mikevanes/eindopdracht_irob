//
// Created by Mike van Es on 13/04/2021.
//

#include "AcceleroDriver.h"
#include "../Defines/AcceleroDefines.h"
#include<Wire.h>
#include <Arduino.h>
#include <MPU9250_WE.h>


AcceleroDriver::AcceleroDriver() {
    this->myMPU9250 = MPU9250_WE(MPU_ADDR);
    this->SUM = 0;
    this->INDEX = 0;
    this->AVERAGED = 0;


    AcceleroDriver::SetInterrupt();

}

int AcceleroDriver::GetAngle() {
    if(!AcceleroDriver::allow_read) return this->compFilter[0];


//    Serial.println(AcceleroDriver::data_ready);
    AcceleroDriver::allow_read = false;

    xyzFloat angles = this->myMPU9250.getAngles();

    this->SUM = this->SUM - this->READINGS[this->INDEX];
    this->READINGS[this->INDEX] = angles.x;
    this->SUM = this->SUM + angles.x;
    this->INDEX = (this->INDEX + 1) % WINDOW_SIZE;

    this->AVERAGED = this->SUM / WINDOW_SIZE;

//    this->compFilter[0] = atan((angles.x/16384.0)/sqrt(pow((angles.z/16384.0),2) + pow((angles.y/16384.0),2)))*(180/PI);

//    this->compFilter[0] = 0.98 *(this->compFilter[0]  + gyr.x*elapsedTime) + 0.02*0.5;
//    this->compFilter[0] = (1-ALPHA)*(this->compFilter[0] + gyr.x * 0.005) + (ALPHA)*(Acceleration_angle);
//    Serial.println(compFilter[0]);
//    Serial.print("compFilter: ");
//    Serial.println(compFilter[0]);

    return AVERAGED;
}

bool AcceleroDriver::SetupWire() {
    Wire.begin();
    if(!myMPU9250.init()){
        Serial.println("MPU9250 does not respond");
    }
    else{
        Serial.println("MPU9250 is connected");
    }

    Serial.println("Position you MPU9250 flat and don't move it - calibrating...");
    delay(1000);
    myMPU9250.autoOffsets();
    Serial.println("Done!");

    myMPU9250.setSampleRateDivider(5);
//    myMPU9250.setSampleRateDivider(99);

    myMPU9250.setAccRange(MPU9250_ACC_RANGE_2G);
//    myMPU9250.setGyrRange(MPU9250_GYRO_RANGE_250);

    /*  Enable/disable the digital low pass filter for the accelerometer
     *  If disabled the bandwidth is 1.13 kHz, delay is 0.75 ms, output rate is 4 kHz
     */
    myMPU9250.enableAccDLPF(true);
//    myMPU9250.enableGyrDLPF();


    /*  Digital low pass filter (DLPF) for the accelerometer, if enabled
     *  MPU9250_DPLF_0, MPU9250_DPLF_2, ...... MPU9250_DPLF_7
     *   DLPF     Bandwidth [Hz]      Delay [ms]    Output rate [kHz]
     *     0           460               1.94           1
     *     1           184               5.80           1
     *     2            92               7.80           1
     *     3            41              11.80           1
     *     4            20              19.80           1
     *     5            10              35.70           1
     *     6             5              66.96           1
     *     7           460               1.94           1
     */
    myMPU9250.setAccDLPF(MPU9250_DLPF_0);
//    myMPU9250.setGyrDLPF(MPU9250_DLPF_0);


    return true;
}

void AcceleroDriver::SetInterrupt() {
    // TIMER 1 for interrupt frequency 400 Hz:
    cli(); // stop interrupts
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1  = 0; // initialize counter value to 0
    // set compare match register for 400 Hz increments
    OCR1A = 39999; // = 16000000 / (1 * 400) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS12, CS11 and CS10 bits for 1 prescaler
    TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    sei(); // allow interrupts

}

ISR(TIMER1_COMPA_vect){
    AcceleroDriver::allow_read = true;
}

bool AcceleroDriver::allow_read = false;