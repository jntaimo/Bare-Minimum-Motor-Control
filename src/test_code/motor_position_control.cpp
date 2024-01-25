#include <Arduino.h>
#include "PID.h"
#include "EncoderVelocity.h"
#include "pinout.h"
#include "EveryNMillis.h"
#include "EveryNMicros.h"
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

unsigned long currentPidLoopStartTime = 0;
unsigned long previousPidLoopStartTime = 0;
unsigned long timeBetweenPidLoopsAccumulator = 0;
int pidLoopIntervalCount = 0;

void setup() {
    driveSetup();
    Serial.begin(); // Specify baud rate
    previousPidLoopStartTime = micros(); // Initialize the first previous start time
}

void loop() {
    // Update PID at 500Hz
    EVERY_N_MICROS(100) {
        currentPidLoopStartTime = micros(); // Record start time of current PID loop

        // Calculate the time between the start of the current and the previous PID loop
        if (pidLoopIntervalCount > 0) { // Skip the first loop to have a previous time to compare
            timeBetweenPidLoopsAccumulator += currentPidLoopStartTime - previousPidLoopStartTime;
        }
        previousPidLoopStartTime = currentPidLoopStartTime; // Update previous start time for the next loop
        pidLoopIntervalCount++;

        // PID control logic
        setpoint = 2 * PI * sin(4*(millis() / 1000.0));
        position = encoder.getPosition();
        controlEffort = motorPID.calculateParallel(setpoint, position);
        controlPower = constrain(controlEffort / 12.0, -1, 1);
        driveVolts(controlEffort);
    }

    // Print values at 10Hz
    EVERY_N_MILLIS(100) {
        if (pidLoopIntervalCount > 1) { // Ensure there's at least one interval to calculate
            // Calculate the average time between PID loop starts
            double averageTimeBetweenPidLoops = (double)timeBetweenPidLoopsAccumulator / (pidLoopIntervalCount - 1);
            // Print position parameters and the average time between PID loop starts
            Serial.printf("Setpoint (rad): %.2f, Position (rad): %.2f, Control Effort (v): %.2f, Control Power: %.3f, Avg Time Between PID Loops (us): %.2f\n",
                          setpoint, position, controlEffort, controlPower, averageTimeBetweenPidLoops);

            // Reset the accumulator and count for the next set of averages
            timeBetweenPidLoopsAccumulator = 0;
            pidLoopIntervalCount = 1; // Reset to 1 to skip the first loop's interval calculation
        }
    }
}
