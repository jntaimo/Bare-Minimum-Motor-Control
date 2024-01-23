#include <Arduino.h>
#include <ESP32Encoder.h>
#include "pinout.h"

ESP32Encoder encoder;
ESP32Encoder encoder2;


void setup(){
	
	Serial.begin(115200);

	// Enable the weak pull down resistors
	ESP32Encoder::useInternalWeakPullResistors=UP;

	encoder.attachFullQuad(LEFT_ENCODER_A_PIN, LEFT_ENCODER_B_PIN);
	encoder2.attachFullQuad(RIGHT_ENCODER_A_PIN, RIGHT_ENCODER_B_PIN);
}

void loop(){
	// Loop and read the count
	Serial.println("Encoder count = " + String((int32_t)encoder.getCount()) + " " + String((int32_t)encoder2.getCount()));
	delay(100);
}