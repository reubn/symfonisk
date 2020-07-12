#include <map>

#include "../../main.hpp"
#include "../../ringLEDs/main.hpp"

#include "./shows/solidColour.hpp"
#include "./shows/rainbowBounce.hpp"

std::map<int, void (*)(ConfigurableSettings& settings, bool first)> shows{{0, loopSolidColour}, {1, loopRainbowBounce}};
int lastShow;
bool lastState;

void initialiseCoordinator(ConfigurableSettings& settings){};

void loopCoordinator(ConfigurableSettings& settings){
  if(settings.showId != lastShow) {
    for(auto& ringLED : allLEDs) LEDStrip.SetPixelColor(ringLED.index, RgbColor(0, 0, 0));
    Serial.println("");
    Serial.println("----- Switch to Show " + String(settings.showId) +  " -----");
    Serial.println("");
  };

  if(settings.on) shows[settings.showId](settings, settings.showId != lastShow || !lastState);
  else if(lastState) {
    for(auto& ringLED : allLEDs) LEDStrip.SetPixelColor(ringLED.index, RgbColor(0, 0, 0));
    LEDStrip.Show();
  }

  lastShow = settings.showId;
  lastState = settings.on;
};
