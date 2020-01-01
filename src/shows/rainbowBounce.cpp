#include <cmath>
#include "../main.hpp"
#include "../ringLEDs/main.hpp"

#include "rainbowBounce.hpp"
float bounceBetween(int &direction, float &value, float increment) {
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

void loopRainbowBounce(ConfigurableSettings& settings){
    static float msBetweenFrames = 1000 / 60; // 60FPS
  	static unsigned long lastExecutionTimestamp = 0;

    if(millis() < lastExecutionTimestamp + msBetweenFrames) return;

    static float maxHue = 0.65;
    static float minHue = 0.4;
    static float diffHue = maxHue - minHue;

    static float seamRelocationFactor = 0.75;

    static float colourOffsetIncrement = 0.001;
    static float colourOffset = 0;

    static NeoGamma<NeoGammaEquationMethod> colorGamma;

    static float saturation = 1;
    static float brightness = settings.brightness / 255.0f;

    static int direction = +1;

    for(auto& ringLED : allLEDs) {
  		float hue = minHue + (std::sin(M_PI * (colourOffset + fmod(ringLED.angle + seamRelocationFactor, 1))) * diffHue);
      LEDStrip.SetPixelColor(ringLED.index, colorGamma.Correct(RgbColor(HsbColor(hue, saturation, brightness))));
  	}

    bounceBetween(direction, colourOffset, colourOffsetIncrement);

  	LEDStrip.Show();
    lastExecutionTimestamp = millis();
}
