#ifndef DRIVE_H
#define DRIVE_H

#define PWM_FREQ 25000
//max number of bits for pwm
#define PWM_BITS 10
#define MAX_PWM (pow(2, PWM_BITS)-1)
#define CHANNEL 0
void driveSetup();
void driveVolts(double volts);
void drive(double power);
#endif // DRIVE_H