#include <Arduino.h>
#include <FastLED.h>
// #include <ESP8266WiFi.h>

#include "main.hpp"
#include "./ringLEDs/main.hpp"
#include "./shows/coordinator/main.hpp"

ConfigurableSettings settings;

void setup() {
	Serial.begin(9600);
  Serial.println("Started");

	// WiFi.forceSleepBegin();

  initialiseLEDs(settings.globalBrightness);
}

void loop() {
  loopCoordinator(settings);
}
