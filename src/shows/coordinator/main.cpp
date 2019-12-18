#include <map>

#include "../../main.hpp"
#include "../../ringLEDs/main.hpp"

#include "./shows/rainbowBreathe.hpp"
#include "./shows/ringFade.hpp"
#include "./shows/solidColour.hpp"
#include "./shows/rainbow.hpp"

std::map<int, void (*)(ConfigurableSettings& settings)> shows{{0, loopRainbowBreathe}, {1, loopRingFade}, {2, loopSolidColour}, {3, loopRainbow}};
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
