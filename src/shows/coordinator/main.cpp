#include <map>

#include "../../main.hpp"
#include "../../ringLEDs/main.hpp"

#include "./shows/solidColour.hpp"
#include "./shows/rainbow.hpp"

std::map<int, void (*)(ConfigurableSettings& settings)> shows{{0, loopSolidColour}, {1, loopRainbow}};
int lastShow;

void initialiseCoordinator(ConfigurableSettings& settings){};

void loopCoordinator(ConfigurableSettings& settings){
  if(settings.showId != lastShow) {
    for(auto& ringLED : allLEDs) rawLEDs[ringLED.index] = CRGB(0, 0, 0);
    Serial.println("Changing Show");
  };

  lastShow = settings.showId;
  shows[settings.showId](settings);
};
