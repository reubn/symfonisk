#include "../main.hpp"
#include "../ringLEDs/main.hpp"

#include "rainbowBreathe.hpp"

void loopRainbowBreathe(ConfigurableSettings& settings){
    static float msBetweenFrames = 1000 / 60; // 60FPS
    static int maxBrightness = 255;
    static int minBrightness = 0;

    static float maxHue = 255;
    static float maxOffset = 255 / maxHue;

    static int topHold = 2750;
    static int bottomHold = 1750;
    static int transitionLength = 3250;
    static int dimmingLength = 1000;
    static float colourOffsetIncrement = 0.004;


  	static unsigned long lastExecutionColour = 0;
  	static unsigned long lastExecutionBrightness = 0;
  	static float brightness = minBrightness;
    static float colourOffset = 0;
  	static int mode = +1;
  	static int hold = 0;
    static boolean blanked = false;

    if(settings.enabled) {
      LEDS.setBrightness(settings.globalBrightness);
      int adjustedBrightness = dim8_lin(min(maxBrightness, max(minBrightness, int(round(brightness)))));

      if(millis() >= lastExecutionBrightness + (hold ? hold : msBetweenFrames)){
        hold = 0;

        for(auto& ringLED : innerLEDs) rawLEDs[ringLED.index] = CHSV(0, 0, maxBrightness - adjustedBrightness);

        if(brightness >= maxBrightness) {hold = topHold; mode = -1;}
        if(brightness <= minBrightness) {hold = bottomHold; mode = +1;}

        float brightnessIncrement = (maxBrightness - minBrightness) / (transitionLength / msBetweenFrames);
        brightness += (brightnessIncrement * mode);

      	FastLED.show();
        lastExecutionBrightness = millis();
      }

      if(millis() >= lastExecutionColour + msBetweenFrames){
        for(auto& ringLED : outerLEDs) {
      		float hue = fmod(ringLED.angle + colourOffset, maxOffset) * maxHue;
      		rawLEDs[ringLED.index] = CHSV(hue, 255, adjustedBrightness);
      	}

      	colourOffset = fmod(colourOffset + colourOffsetIncrement, maxOffset);

      	FastLED.show();
        lastExecutionColour = millis();
      }
      blanked = false;
    } else if(!blanked && millis() >= lastExecutionBrightness + msBetweenFrames){
      hold = 0;

      int clampedBrightness = min(settings.globalBrightness, max(0, int(round(brightness))));
      LEDS.setBrightness(clampedBrightness);

      if(clampedBrightness <= 0) blanked = true;

      float dimmingIncrement = maxBrightness / (dimmingLength / msBetweenFrames);
      brightness -= dimmingIncrement;

    	FastLED.show();
      lastExecutionBrightness = millis();
    }
}
