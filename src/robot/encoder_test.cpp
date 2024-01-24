#include "EncoderVelocity.h"
#include "pinout.h"


#define COUNTS_PER_REVOLUTION 103.8

#define PRINT_DELAY 30 // Delay between printing to serial in milliseconds
#define TAU 0.01 // Time constant for velocity filter in seconds
static unsigned long lastPrintTime = 0;

// Encoder velocity readers
EncoderVelocity leftEncoder(LEFT_ENCODER_A_PIN, LEFT_ENCODER_B_PIN, COUNTS_PER_REVOLUTION, TAU);
EncoderVelocity rightEncoder(RIGHT_ENCODER_A_PIN, RIGHT_ENCODER_B_PIN, COUNTS_PER_REVOLUTION, TAU);

void setup() {
    Serial.begin(115200);
}

//Prints the encoder readings to the serial monitor
void printEncoderReadings(){
    Serial.printf("L Encoder: V: %f, P: %f, R Encoder: V: %f, P: %f\n", 
    leftEncoder.getVelocity(), leftEncoder.getPosition(), rightEncoder.getVelocity(), rightEncoder.getPosition());
 }

void loop(){
    // Print encoder readings every PRINT_DELAY milliseconds
    if (millis() - lastPrintTime >= PRINT_DELAY) {
        lastPrintTime = millis();
        printEncoderReadings();
    }
    
}