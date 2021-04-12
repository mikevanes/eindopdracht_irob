#include <Arduino.h>
#include <Drivers/MotorDriver.h>

MotorDriver* md;

void setup() {
// write your initialization code here
    md = new MotorDriver(Steps::FULL, 500);
    md->SetupPins();

    Serial.begin(9600);
}

void loop() {
    // write your code here
    md->TurnLeftMotor();
    md->TurnRightMotor();


    //HALLO.
}