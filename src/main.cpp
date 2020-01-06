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

class PixelHandler : public LightHandler {
  private:
    HueLightInfo _info;
  public:
    void handleQuery(int lightNumber, HueLightInfo newInfo, aJsonObject* raw) {
      // define the effect to apply, in this case linear blend
      HsbColor newColour = getHsb(newInfo.hue, newInfo.saturation, newInfo.brightness);
      // RgbColor originalColor = strip.GetPixelColor(0);
      Serial.print("Effect: "); Serial.println(newInfo.effect);

      _info = newInfo;

      if (newInfo.on) {
        if (newInfo.effect == EFFECT_COLORLOOP) {
          settings.showId = 4;
        } else {
					Serial.print("Hue: "); Serial.println(newColour.H);
					Serial.print("Saturation: "); Serial.println(newColour.S);
					Serial.print("Brightness: "); Serial.println(newColour.B);


					settings.colour = newColour;
					settings.showId = 0;
				}
      }
      else {
				Serial.println("TURN OFF");
				settings.colour = HsbColor(settings.colour.H, settings.colour.S, 0.0f);

				settings.showId = 0;
      }
    }

    HueLightInfo getInfo(int lightNumber) { return _info; }
};

void setup() {
	Serial.begin(115200);
  // while (!Serial); // wait for serial attach

  Serial.println();
  Serial.println("Initializing...");
  Serial.flush();

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

	LightService.begin();

	LightService.setLightHandler(0, new PixelHandler());

	if (timeStatus() == timeSet) {
    Serial.println(NTP.getTimeDateString(now()));
  }
}

void loop() {
	LightService.update();
  loopCoordinator(settings);
}
