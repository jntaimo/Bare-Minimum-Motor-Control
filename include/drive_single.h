#ifndef DRIVE_H
#define DRIVE_H
//gobilda motor counts
//https://www.gobilda.com/yellow-jacket-planetary-gear-motors/
#define CPR_30_RPM 5281.1
#define CPR_60_RPM 2786.2
#define CPR_312_RPM 537.7

#define PWM_FREQ 25000
//max number of bits for pwm
#define PWM_BITS 10
#define MAX_PWM (pow(2, PWM_BITS)-1)
#define CHANNEL 0
void driveSetup();
void driveVolts(double volts);
void drive(double power);
#endif // DRIVE_H