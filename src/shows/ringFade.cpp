#include <cmath>
#include <vector>

#include "../main.hpp"
#include "../ringLEDs/main.hpp"

#include "ringFade.hpp"

void loopRingFade(ConfigurableSettings& settings) {
  static float msBetweenFrames = 1000 / 60; // 60FPS

  static unsigned long lastExecution = 0;
	static int brightness = 10;
	static int mode = 1;

  if(millis() >= lastExecution + msBetweenFrames){
    for(auto& ringLED : outerLEDs) rawLEDs[ringLED.index] = CHSV(0, 0, brightness);
    for(auto& ringLED : innerLEDs) rawLEDs[ringLED.index] = CHSV(0, 0, 255 - brightness);

    if(brightness >= 255) mode = -1;
    if(brightness <= 10) mode = +1;

  	brightness = brightness + mode;
  	FastLED.show();
  }
}
