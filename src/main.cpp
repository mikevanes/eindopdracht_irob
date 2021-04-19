#include <Arduino.h>
#include <Drivers/MotorDriver.h>
#include <Defines/MotorDefines.h>

#include <Drivers/AcceleroDriver.h>
#include <Controller/PIDcontroller.h>

MotorDriver* md;
AcceleroDriver* ad;
PIDcontroller* pidC;
float elapsedTime, time, timePrev;

void setup() {
// write your initialization code here
    Serial.begin(115200);
    md = new MotorDriver(Steps::HALF, MAX_RPM, MAX_RPM);
    ad = new AcceleroDriver();
    pidC = new PIDcontroller();

    if(!ad->SetupWire()){
//        Serial.println("Program crashed whilst initialising Accelero driver");
    }

    time = millis();


}

void turnMotor(){
    // write your code here
//    md->TurnLeftMotor();
    md->TurnRightMotor();
}

void loop() {
    timePrev = time;
    time = micros();
    elapsedTime = (time - timePrev) / 1000000;

    float angle = ad->GetAngle();
//    Serial.println(angle, 5);

    float pid = abs(pidC->GetPID(angle, elapsedTime));

    Serial.println(pid);

//
    if(angle > 5){
//        md->SetDirection(LEFT_MOTOR_DIR, TURN_RIGHT);
        md->SetDirection(RIGHT_MOTOR_DIR, TURN_RIGHT);

//        md->SetLeftMotorSpeed(pid);
        md->SetRightMotorSpeed(pid);

        turnMotor();
    }else if(angle < -5){
//        md->SetDirection(LEFT_MOTOR_DIR, TURN_LEFT);
        md->SetDirection(RIGHT_MOTOR_DIR, TURN_LEFT);

//        md->SetLeftMotorSpeed(pid);
        md->SetRightMotorSpeed(pid);

        turnMotor();
    }

}
