#include <vector>

#include "../main.hpp"
#include "../ringLEDs/main.hpp"

#include "solidColour.hpp"

void loopSolidColour(ConfigurableSettings& settings) {
  static float msBetweenFrames = 1000 / 60; // 60FPS
  static unsigned long lastExecution = millis();

  if(millis() < lastExecution + msBetweenFrames) return;

  if(settings.enabled) for(auto& ringLED : allLEDs) LEDStrip.SetPixelColor(ringLED.index, settings.colour);
  else for(auto& ringLED : allLEDs) LEDStrip.SetPixelColor(ringLED.index, RgbColor(0, 0, 0));
	LEDStrip.Show();
}
