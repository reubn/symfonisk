#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <NtpClientLib.h>
#include "./LightService.h"

// #include <FS.h>

#include "./secrets.h"

#include "main.hpp"
#include "./ringLEDs/main.hpp"
#include "./shows/coordinator/main.hpp"

ConfigurableSettings settings;
LightServiceClass LightService;

HsbColor getHsb(int hue, int sat, int bri) {
  float H, S, B;
  H = ((float)hue) / 182.04 / 360.0;
  S = ((float)sat) / COLOR_SATURATION;
  B = ((float)bri) / COLOR_SATURATION;
  return HsbColor(H, S, B);
}

void interpretQuery(HueLightInfo& _info, HueLightInfo& newInfo) {
  _info = newInfo;

  Serial.println("");
  Serial.println("----- Query -----");
  Serial.print("on: "); Serial.println(_info.on);
  Serial.print("effect: "); Serial.println(_info.effect);

  Serial.println("");
  Serial.print("raw hue: "); Serial.println(_info.hue);
  Serial.print("raw saturation: "); Serial.println(_info.saturation);
  Serial.print("raw brightness: "); Serial.println(_info.brightness);


  if(_info.on) {
    // Hack to stop Alexa removing effect
    if (_info.effect == EFFECT_COLORLOOP || (_info.hue == 4938 && _info.saturation == 114 && _info.brightness == 0)) {
      settings.showId = 4;
    } else {
      if(_info.brightness == 0) {
        _info.brightness = 254;
      }

      HsbColor newColour = getHsb(_info.hue, _info.saturation, _info.brightness);

      settings.colour = newColour;

      settings.showId = 0;
    }
  } else {
    _info.brightness = 0;
    settings.colour = HsbColor(settings.colour.H, settings.colour.S, 0.0f);

    settings.showId = 0;
  }

  Serial.println("");
  Serial.print("show id: "); Serial.println(settings.showId);
  Serial.println("");

  Serial.print("display hue: "); Serial.println(settings.colour.H);
  Serial.print("display saturation: "); Serial.println(settings.colour.S);
  Serial.print("display brightness: "); Serial.println(settings.colour.B);

  Serial.println("-----------------");
}

class PixelHandler : public LightHandler {
  public:
    HueLightInfo _info;
    void handleQuery(int lightNumber, HueLightInfo newInfo, aJsonObject* raw) {
      interpretQuery(_info, newInfo);
    }

    string getFriendlyName(int lightNumber) {
      return "Symfonisk Light" DEVICE_NAME;
    }

    HueLightInfo getInfo(int lightNumber) { return _info; }
};

void setup() {
	Serial.begin(115200);
  // while (!Serial); // wait for serial attach

  Serial.println("Initializing...");

  initialiseLEDs();
	// SPIFFS.begin();
	// SPIFFS.format();

	WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

	NTP.begin("pool.ntp.org", 0, true);

  PixelHandler* pixelHandler = new PixelHandler();

  pixelHandler->_info.on = true;
  pixelHandler->_info.hue = 0;
  pixelHandler->_info.saturation = 0;
  pixelHandler->_info.brightness = 0;
  pixelHandler->_info.effect = EFFECT_COLORLOOP;

	LightService.begin();

  interpretQuery(pixelHandler->_info, pixelHandler->_info);

	LightService.setLightHandler(0, pixelHandler);

	if(timeStatus() == timeSet) {
    Serial.println(NTP.getTimeDateString(now()));
  }
}

void loop() {
	LightService.update();
  loopCoordinator(settings);
}
