#include <cmath>

#include "../main.hpp"
#include "../ringLEDs/main.hpp"

#include "wipe.hpp"

NeoGamma<NeoGammaEquationMethod> colorGamma;

void loopWipe(ConfigurableSettings& settings){
    static float msBetweenFrames = 1000 / 60; // 60FPS
  	static unsigned long lastExecutionTimestamp = 0;

    if(millis() < lastExecutionTimestamp + msBetweenFrames) return;

    static float maxHue = 1;
    static float maxOffset = 1 / maxHue;

    static float colourOffsetIncrement = 0.003;
    static float colourOffset = 0;

    static float angleOffsetIncrement = (1 / msBetweenFrames) / 4;
    static float angleOffset = 0;

    static float saturation = 1;

    for(auto& ringLED : outerLEDs) {
  		float hue = fmod(ringLED.angle + colourOffset, maxOffset) * maxHue;
      float brightness = 1 - std::sin(M_PI * fabs(angleOffset - ringLED.angle));
      if(brightness < 0.06 && brightness != 0) brightness = 0.06;
      // Serial.println(brightness);
      LEDStrip.SetPixelColor(ringLED.index, colorGamma.Correct(RgbColor(HsbColor(hue, saturation, brightness))));
  	}

    for(auto& ringLED : innerLEDs) {
  		float hue = fmod(ringLED.angle - colourOffset, maxOffset) * maxHue;
      float brightness = std::sin(M_PI * fabs(angleOffset - ringLED.angle));
      if(brightness < 0.06 && brightness != 0) brightness = 0.06;
      // Serial.println(brightness);
      LEDStrip.SetPixelColor(ringLED.index, colorGamma.Correct(RgbColor(HsbColor(hue, saturation, brightness))));
  	}

  	colourOffset = fmod(colourOffset + colourOffsetIncrement, maxOffset);
    angleOffset = fmod(angleOffset + angleOffsetIncrement, 1);
  	LEDStrip.Show();
    lastExecutionTimestamp = millis();
}
