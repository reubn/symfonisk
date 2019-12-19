#include <Arduino.h>
#include <FastLED.h>
// #include <ESP8266WiFi.h>

#include "main.hpp"
#include "./ringLEDs/main.hpp"
#include "./shows/coordinator/main.hpp"

ConfigurableSettings settings;

void setup() {
	Serial.begin(115200);
  while (!Serial); // wait for serial attach

  Serial.println();
  Serial.println("Initializing...");
  Serial.flush();

	// WiFi.forceSleepBegin();

  initialiseLEDs();
}

void loop() {
  loopCoordinator(settings);
}
