#include <Arduino.h>
#include <Drivers/MotorDriver.h>
#include <Defines/MotorDefines.h>
#include "Defines/PIDDefines.h"

#include <Drivers/AcceleroDriver.h>
#include <Controller/PIDcontroller.h>

MotorDriver* md;
AcceleroDriver* ad;
PIDcontroller* pidC;
float elapsedTime, time, timePrev;
bool forward = false;
bool bootUp = true;

void setup() {
    // write your initialization code here
    Serial.begin(115200);
    md = new MotorDriver();
    ad = new AcceleroDriver();
    pidC = new PIDcontroller();

    if(!ad->SetupWire()){
        //Serial.println("Program crashed whilst initialising Accelero driver");
    }

    time = micros();
}

void turnMotor(){
    // write your code here
    md->TurnLeftMotor();
//    md->TurnRightMotor();
}

void SetStep(double pid){
    pid = abs(pid);
    if(pid < 300){
        md->SetStep(Steps::SIXTEENTH);
    }

    else if(pid < 800){
        md->SetStep(Steps::QUARTER);
    }


//    else if(pid > 700){
//        md->SetStep(Steps::HALF);
//    }
}

void loop() {
    time = micros();
    elapsedTime = (time - timePrev)/1000;
    int angle = ad->GetAngle();

    double pid = pidC->GetPID(angle, elapsedTime);

    SetStep(pid);

    if(abs(angle) > 0) {
        if ((angle >= 0 && !forward) || (angle >= 0 && bootUp)) {
            md->SetDirection(RIGHT_MOTOR_DIR, TURN_LEFT);
            md->SetDirection(LEFT_MOTOR_DIR, TURN_LEFT);

            forward = true;
            bootUp = false;
        } else if ((angle < 0 && forward) || (angle < 1 && bootUp)) {
            md->SetDirection(RIGHT_MOTOR_DIR, TURN_RIGHT);
            md->SetDirection(LEFT_MOTOR_DIR, TURN_RIGHT);

            forward = false;
            bootUp = false;
        }

        pid = abs(pid);

        pid = MAX_SPEED - pid;
        pid = pid <= MIN_SPEED ? MIN_SPEED : pid;

        md->SetLeftMotorSpeed(pid);

        turnMotor();
    }

    timePrev = time;
}


