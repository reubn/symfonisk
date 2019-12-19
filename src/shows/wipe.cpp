#include <cmath>

#include "../main.hpp"
#include "../ringLEDs/main.hpp"

#include "wipe.hpp"

NeoGamma<NeoGammaEquationMethod> colorGamma;

void loopWipe(ConfigurableSettings& settings){
    static float msBetweenFrames = 1000 / 60; // 60FPS
  	static unsigned long lastExecutionTimestamp = 0;

    if(millis() < lastExecutionTimestamp + msBetweenFrames) return;

    // Serial.println(r);

    static float maxHue = 1;
    static float maxOffset = 1 / maxHue;

    static float colourOffsetIncrement = 0.003;
    static float colourOffset = 0;

    static float angleOffsetIncrement = (1 / msBetweenFrames) / 3;
    static float angleOffset = 0;

    static float saturation = 1;

    for(auto& ringLED : allLEDs) {
  		float hue = fmod(ringLED.angle + colourOffset, maxOffset) * maxHue;
      // float brightness = 1 - std::min((std::sin(M_PI * fabs(angleOffset - ringLED.angle)) * 3), 1.0d);
      float brightness = 1 - std::sin(M_PI * fabs(angleOffset - ringLED.angle));
      // Serial.println(brightness);
      // if(brightness <= 0.1) brightness = 0;
      LEDStrip.SetPixelColor(ringLED.index, colorGamma.Correct(RgbColor(HsbColor(hue, saturation, brightness))));
  	}

  	colourOffset = fmod(colourOffset + colourOffsetIncrement, maxOffset);
    angleOffset = fmod(angleOffset + angleOffsetIncrement, 1);
  	LEDStrip.Show();
    lastExecutionTimestamp = millis();
}
