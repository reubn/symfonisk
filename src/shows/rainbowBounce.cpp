#include <cmath>
#include "../main.hpp"
#include "../ringLEDs/main.hpp"

#include "rainbowBounce.hpp"

void bounceBetween(int &direction, float &value, float increment) {
  if(value + (increment * direction) > 1) {
    value = 1 - fmod(value + increment, 1);
    direction = -1;
  }
  else if(value + (increment * direction) < 0) {
    value = abs(fmod(value - increment, 1));
    direction = +1;
  }
  else value = fmod(value + (increment * direction), 1);
}

void loopRainbowBounce(ConfigurableSettings& settings, bool first){
    static float msBetweenFrames = 1000 / 60; // 60FPS
  	static unsigned long lastExecutionTimestamp = 0;

    if(millis() < lastExecutionTimestamp + msBetweenFrames) return;

    static float hueLocator = 0.5;
    static int directionHueLocator = +1;
    static float hueLocatorOffsetUp = 0.15;
    static float hueLocatorOffsetDown = 0.1;

    static float maxHue = hueLocator + hueLocatorOffsetUp;
    static float minHue = hueLocator - hueLocatorOffsetDown;
    static float diffHue = maxHue - minHue;

    static float seamRelocationFactor = 0.75;

    static float colourOffsetIncrement = 0.001;
    static float colourOffset = 0;

    static NeoGamma<NeoGammaEquationMethod> colorGamma;

    static float saturation = 1;
    float brightness = settings.colour.B;

    static int direction = +1;

    for(auto& ringLED : allLEDs) {
  		float hue = minHue + (std::sin(M_PI * (colourOffset + fmod(ringLED.angle + seamRelocationFactor, 1))) * diffHue);
      LEDStrip.SetPixelColor(ringLED.index, colorGamma.Correct(RgbColor(HsbColor(hue, saturation, brightness))));
  	}

    bounceBetween(direction, colourOffset, colourOffsetIncrement);

    // Gradually changes hues faded between
    bounceBetween(directionHueLocator, hueLocator, 0.0001);
    maxHue = (hueLocatorOffsetDown + (hueLocator * ((1 - hueLocatorOffsetUp) - hueLocatorOffsetDown))) + hueLocatorOffsetUp;
    minHue = (hueLocatorOffsetDown + (hueLocator * ((1 - hueLocatorOffsetUp) - hueLocatorOffsetDown))) - hueLocatorOffsetDown;

  	LEDStrip.Show();
    lastExecutionTimestamp = millis();
}
