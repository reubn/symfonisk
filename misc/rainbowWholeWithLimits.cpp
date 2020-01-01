#include "../main.hpp"
#include "../ringLEDs/main.hpp"

#include "rainbow.hpp"

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

void loopRainbow(ConfigurableSettings& settings){
    static float msBetweenFrames = 1000 / 60; // 60FPS
  	static unsigned long lastExecutionTimestamp = 0;

    if(millis() < lastExecutionTimestamp + msBetweenFrames) return;

    static float maxHue = 0.5;
    static float minHue = 0;
    static float diffHue = maxHue - minHue;

    static float colourOffsetIncrement = 0.01;
    static float colourOffset = 0;

    static float saturation = 1;
    static float brightness = settings.brightness / 255.0f;

    static int direction = +1;

    for(auto& ringLED : allLEDs) {
  		float hue = minHue + (fmod(colourOffset, 1) * diffHue);
      LEDStrip.SetPixelColor(ringLED.index, HsbColor(hue, saturation, brightness));
  	}

    bounceBetween(direction, colourOffset, colourOffsetIncrement);

  	LEDStrip.Show();
    lastExecutionTimestamp = millis();
}
