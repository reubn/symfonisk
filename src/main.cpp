#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>

#include "./secrets.h"

#include "main.hpp"
#include "webServer.hpp"
#include "./ringLEDs/main.hpp"
#include "./shows/coordinator/main.hpp"

ConfigurableSettings settings;
WiFiManager wifiManager;

void configModeCallback(WiFiManager *wM) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());

  settings.on = true;
  settings.showId = 0;
  settings.colour = RgbColor(255, 0, 0);
}

void setup() {
	Serial.begin(115200);
  Serial.println("Initializing...");

  initialiseLEDs();
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setConfigPortalTimeout(5 * 60);
  wifiManager.autoConnect("Symfonisk Bulb", "cats-rats-egotistical-bats");

  if(WiFi.status() == WL_CONNECTED){
    Serial.println("Conected to WiFi");
    setupServer();

    settings.on = true;
    settings.showId = 0;
    settings.colour = RgbColor(0, 255, 0);
  } else {
    Serial.println("WiFi has failed to connect. Restarting");
    ESP.restart();
  }
}

void loop() {
  loopCoordinator(settings);
  loopServer();
}
