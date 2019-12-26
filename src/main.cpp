#include <Arduino.h>
#include <FastLED.h>
// #include <ESP8266WiFi.h>

#include "main.hpp"
#include "./ringLEDs/main.hpp"
#include "./shows/coordinator/main.hpp"

ConfigurableSettings settings;

// bool lastState = false;

void setup() {
	// pinMode(D1, INPUT);

	Serial.begin(115200);
  // while (!Serial); // wait for serial attach

  Serial.println();
  Serial.println("Initializing...");
  Serial.flush();

	// WiFi.forceSleepBegin();

  initialiseLEDs();
}

void loop() {
  loopCoordinator(settings);
	// bool state = digitalRead(D1) == LOW;
	// Serial.println(digitalRead(5));
	// if(state != lastState) {
	// 	Serial.println("CHANGE");
	// 	settings.showId = (settings.showId + 1) % shows.size();
	// }
	// lastState = state;
}
