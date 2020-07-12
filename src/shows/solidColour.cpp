#include <vector>

#include "../main.hpp"
#include "../ringLEDs/main.hpp"

#include "solidColour.hpp"

void loopSolidColour(ConfigurableSettings& settings, bool first) {
  static float msBetweenFrames = 1000 / 60; // 60FPS
  static unsigned long lastExecution = millis();

  static RgbColor lastColour = RgbColor(0, 0, 0);

  if(!first && lastColour == settings.colour) return;
  if(millis() < lastExecution + msBetweenFrames) return;

  for(auto& ringLED : allLEDs) LEDStrip.SetPixelColor(ringLED.index, settings.colour);

  lastColour = settings.colour;
	LEDStrip.Show();
}
