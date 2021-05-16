#include <Arduino.h>
#include <Drivers/MotorDriver.h>
#include <Defines/MotorDefines.h>

#include <Drivers/AcceleroDriver.h>

MotorDriver* md;
AcceleroDriver* ad;

void setup() {
    // write your initialization code here
    Serial.begin(115200);
    md = new MotorDriver();
    ad = new AcceleroDriver();

    if(!ad->SetupWire()){
        Serial.println("Program crashed whilst initialising Accelero driver");
    }
}

void loop() {
    int angle = ad->GetAngle();

    if (angle > 0) {
        md->SetDirection(RIGHT_MOTOR_DIR, TURN_LEFT);
        md->SetDirection(LEFT_MOTOR_DIR, TURN_LEFT);
    } else if (angle < 0) {
        md->SetDirection(RIGHT_MOTOR_DIR, TURN_RIGHT);
        md->SetDirection(LEFT_MOTOR_DIR, TURN_RIGHT);
    }

    md->TurnLeftMotor();
    md->TurnRightMotor();
}


