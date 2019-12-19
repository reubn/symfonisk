#include "../main.hpp"
#include "../ringLEDs/main.hpp"

#include "rainbow.hpp"

void loopRainbow(ConfigurableSettings& settings){
    static float msBetweenFrames = 1000 / 60; // 60FPS
  	static unsigned long lastExecutionTimestamp = 0;

    if(millis() < lastExecutionTimestamp + msBetweenFrames) return;

    static float maxHue = 1;
    static float maxOffset = 1 / maxHue;

    static float colourOffsetIncrement = 0.003;
    static float colourOffset = 0;

    static float saturation = 1;
    static float brightness = settings.brightness / 255.0f;

    for(auto& ringLED : allLEDs) {
  		float hue = fmod(ringLED.angle + colourOffset, maxOffset) * maxHue;
      LEDStrip.SetPixelColor(ringLED.index, HsbColor(hue, saturation, brightness));
  	}

  	colourOffset = fmod(colourOffset + colourOffsetIncrement, maxOffset);

  	LEDStrip.Show();
    lastExecutionTimestamp = millis();
}
