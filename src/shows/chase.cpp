#include <vector>
#include <algorithm>

#include "../main.hpp"
#include "../ringLEDs/main.hpp"

#include "chase.hpp"

bool sorted = false;

void loopChase(ConfigurableSettings& settings) {
  static float msBetweenFrames = 1000 / 20;
  static unsigned long lastExecutionTimestamp = millis();

  static std::vector<float> orderedAngles;
  static int currentIndex = 0;

  static float maxHue = 1;
  static float maxOffset = 1 / maxHue;

  static float colourOffsetIncrement = 0.003;
  static float colourOffset = 0;

  static float saturation = 1;
  static float brightness = settings.brightness / 255.0f;

  if(millis() < lastExecutionTimestamp + msBetweenFrames) return;

  if(!sorted) {
    for (int index = 0, size = allLEDs.size(); index < size; ++index){
      float angle = allLEDs[index].angle;
      if(!std::count(orderedAngles.begin(), orderedAngles.end(), angle)) orderedAngles.push_back(angle);
    }

    std::sort(orderedAngles.begin(), orderedAngles.end());
    sorted = true;
  }


  for(auto& ringLED : allLEDs) {
    float hue = fmod(ringLED.angle + colourOffset, maxOffset) * maxHue;
    if(ringLED.angle == orderedAngles[currentIndex]) LEDStrip.SetPixelColor(ringLED.index, HsbColor(hue, saturation, brightness));
    else LEDStrip.SetPixelColor(ringLED.index, RgbColor(0, 0, 0));
  }

  currentIndex = (currentIndex + 1) % orderedAngles.size();
	colourOffset = fmod(colourOffset + colourOffsetIncrement, maxOffset);

	LEDStrip.Show();
  lastExecutionTimestamp = millis();
}



//
//   static float msBetweenFrames = 1000 / 2;
//   static unsigned long lastExecutionTimestamp = millis();
//
//   static int currentIndex = 0;
//
//   if(millis() >= lastExecutionTimestamp + msBetweenFrames){
//   for(auto& ringLED : ordered) {
//     if(ringLED.index == currentIndex) {
//       LEDStrip.SetPixelColor(ringLED.index, HsbColor(settings.hue / 255.0f, settings.saturation / 255.0f, settings.brightness / 255.0f));
//     }
//     else LEDStrip.SetPixelColor(ringLED.index, RgbColor(0, 0, 0));
//   };
//   currentIndex = (currentIndex + 1) % ordered.size();
// 	LEDStrip.Show();
//   lastExecutionTimestamp = millis();
// }
// }
