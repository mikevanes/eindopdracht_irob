#include <Arduino.h>
#include <Drivers/MotorDriver.h>
#include <Defines/MotorDefines.h>

#include <Drivers/AcceleroDriver.h>

MotorDriver* md;
AcceleroDriver* ad;

void setup() {
// write your initialization code here
    md = new MotorDriver(Steps::FULL, MAX_RPM, MAX_RPM);
    ad = new AcceleroDriver();
//    Serial.begin(115200);
}

void loop() {
//   Serial.println(ad->GetAngle());
    if(ad->GetAngle() > 0){
        md->SetDirection(LEFT_MOTOR_DIR, TURN_LEFT);
        md->SetDirection(RIGHT_MOTOR_DIR, TURN_LEFT);
    }else{
        md->SetDirection(LEFT_MOTOR_DIR, TURN_RIGHT);
        md->SetDirection(RIGHT_MOTOR_DIR, TURN_RIGHT);
    }
    // write your code here
    md->TurnLeftMotor();
    md->TurnRightMotor();


    //HALLO.
}