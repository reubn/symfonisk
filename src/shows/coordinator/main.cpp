#include <map>

#include "../../main.hpp"
#include "../../ringLEDs/main.hpp"

#include "./shows/solidColour.hpp"
#include "./shows/rainbow.hpp"
#include "./shows/rainbowBounce.hpp"
#include "./shows/chase.hpp"
#include "./shows/wipe.hpp"

std::map<int, void (*)(ConfigurableSettings& settings)> shows{{0, loopSolidColour}, {1, loopRainbow}, {2, loopChase}, {3, loopWipe}, {4, loopRainbowBounce}};
int lastShow;

void initialiseCoordinator(ConfigurableSettings& settings){};

void loopCoordinator(ConfigurableSettings& settings){
  if(settings.showId != lastShow) {
    for(auto& ringLED : allLEDs) LEDStrip.SetPixelColor(ringLED.index, RgbColor(0, 0, 0));
    Serial.println("Changing Show");
  };

  lastShow = settings.showId;
  shows[settings.showId](settings);
};
