#include "../main.hpp"
#include "../ringLEDs/main.hpp"

#include "rainbow.hpp"

void loopRainbow(ConfigurableSettings& settings){
    static float msBetweenFrames = 1000 / 60; // 60FPS
    static int maxBrightness = 255;
    static int minBrightness = 0;

    static float maxHue = 255;
    static float maxOffset = 255 / maxHue;

    static int dimmingLength = 1000;
    static float colourOffsetIncrement = 0.003;


  	static unsigned long lastExecutionColour = 0;
  	static unsigned long lastExecutionBrightness = 0;
  	static float brightness = maxBrightness;
    static float colourOffset = 0;
    static boolean blanked = false;

    if(settings.enabled) {
      brightness = maxBrightness;
      LEDS.setBrightness(settings.globalBrightness);
      int adjustedBrightness = dim8_lin(min(maxBrightness, max(minBrightness, int(round(brightness)))));

      if(millis() >= lastExecutionColour + msBetweenFrames){
        for(auto& ringLED : allLEDs) {
      		float hue = fmod(colourOffset, maxOffset) * maxHue;
      		rawLEDs[ringLED.index] = CHSV(hue, 255, adjustedBrightness);
      	}

      	colourOffset = fmod(colourOffset + colourOffsetIncrement, maxOffset);

      	FastLED.show();
        lastExecutionColour = millis();
      }
      blanked = false;
    } else if(!blanked && millis() >= lastExecutionBrightness + msBetweenFrames){

      int clampedBrightness = min(settings.globalBrightness, max(0, int(round(brightness))));
      LEDS.setBrightness(clampedBrightness);

      if(clampedBrightness <= 0) blanked = true;

      float dimmingIncrement = maxBrightness / (dimmingLength / msBetweenFrames);
      brightness -= dimmingIncrement;

    	FastLED.show();
      lastExecutionBrightness = millis();
    }
}
