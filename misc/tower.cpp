#include <vector>
#include <algorithm>

#include "../main.hpp"
#include "../ringLEDs/main.hpp"

#include "tower.hpp"

NeoGamma<NeoGammaEquationMethod> colorGamma;

void loopTower(ConfigurableSettings& settings) {
  static float msBetweenFrames = 1000 / 1;
  static unsigned long lastExecutionTimestamp = millis();

  static float saturation = settings.saturation / 255.0f;
  static float brightness = settings.brightness / 255.0f;

  static int currentRing = 0;

  if(millis() < lastExecutionTimestamp + msBetweenFrames) return;

  for(auto& ringLED : allLEDs) {
    if(ringLED.ring == currentRing) LEDStrip.SetPixelColor(ringLED.index, colorGamma.Correct(RgbColor(HsbColor(((float)currentRing) / ringCount, saturation, brightness))));
    else LEDStrip.SetPixelColor(ringLED.index, RgbColor(0, 0, 0));
  }

  currentRing = (currentRing + 1) % ringCount;

	LEDStrip.Show();
  lastExecutionTimestamp = millis();
}
