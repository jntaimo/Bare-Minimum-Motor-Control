#include <Arduino.h>
#include "pinout.h"
#include "drive_single.h"


double batteryVoltage = 12.0; //volts

void driveSetup(){
    //configure pins as outputs
    pinMode(DIR1, OUTPUT);
    pinMode(PWM1, OUTPUT);

    //configure pwm channels
    ledcSetup(CHANNEL, PWM_FREQ, PWM_BITS);

    //assign pwm pins to channels
    ledcAttachPin(PWM1, CHANNEL);
}

//drives the motors with units in volts
void driveVolts(double volts){
    drive(volts/batteryVoltage);
}

//drive motors with values from -1 to 1 
//positive values move the motor forward
void drive(double power){
    //limit drive pwm 
    power = constrain(power, -0.9999, 0.9999);
    //pick direction
    digitalWrite(DIR1, power > 0);

    //output pwm
    ledcWrite(power, abs(power)*(MAX_PWM));
}
