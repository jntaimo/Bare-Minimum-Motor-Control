#include <Arduino.h>
#include "PID.h"
#include "EncoderVelocity.h"
#include "pinout.h"
#include "EveryNMillis.h"
#include "drive_single.h"

double kp = 5;
double ki = 0;
double kd = 0;

double tau = 0.1; //seconds

double setpoint = 0; //radians
double position = 0; //radians
double velocity = 0; //radians per second
double controlEffort = 0; //volts
double controlPower = 0; //watts

PID motorPID(kp, ki, kd, 0, tau, false);

#define COUNTS_PER_REVOLUTION 537.7 //312 RPM
EncoderVelocity encoder(LEFT_ENCODER_A_PIN, LEFT_ENCODER_B_PIN, COUNTS_PER_REVOLUTION);

void setup() {
    driveSetup();
    Serial.begin();
}


void loop(){
    //update PID at 500Hz
    EVERY_N_MILLIS(2){
        //update setpoint
        setpoint = 2*PI*sin((millis()/1000.0));
        //update PID tuning
            //motorPID.setParallelTunings(kp, ki, kd);
        //get current position
        position = encoder.getPosition();
        velocity = encoder.getVelocity();
        //position or velocity control (only uncomment one)
        controlEffort = motorPID.calculateParallel(setpoint, position);
        controlPower = constrain(controlEffort/12.0,-1,1);
        //controlEffort = motorPID.calculateParallel(setpoint, velocity);
        //drive the motor
        driveVolts(controlEffort);
    }
    //print values at 10Hz
    EVERY_N_MILLIS(100){
        //print velocity parameters
        //Serial.printf("Setpoint (rad/s): %.2f, Velocity (rad/s): %.2f, Control Effort (v): %.2f\n", setpoint, controlEffort);
        //print position parameters
        Serial.printf("Setpoint (rad): %.2f, Position (rad): %.2f, Control Effort (v): %.2f, Control Power: %.3f\n", setpoint, position, controlEffort, controlPower);

    }
    
}