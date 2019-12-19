#include "main.hpp"

#define DATA_PIN 2
#define NUMBER_OF_LEDS 20

NeoPixelBus<NeoGrbFeature, NeoEsp8266Dma800KbpsMethod> LEDStrip(NUMBER_OF_LEDS, DATA_PIN); // Data Pin is ignored as RX is always used

std::vector<RingLED> outerLEDs {
	{0, 0.917, outer}, {1, 0, outer}, {2, 0.083, outer}, {3, 0.167, outer}, {4, 0.25, outer}, {5, 0.333, outer}, {6, 0.417, outer}, {7, 0.5, outer}, {8, 0.583, outer}, {9, 0.667, outer}, {10, 0.75, outer}, {11, 0.833, outer}
};

std::vector<RingLED> innerLEDs {
	{12, 0.125, inner}, {13, 0.25, inner}, {14, 0.375, inner}, {15, 0.5, inner}, {16, 0.625, inner}, {17, 0.75, inner}, {18, 0.875, inner}, {19, 0, inner}
};

std::vector<RingLED> allLEDs;

void initialiseLEDs(){
  allLEDs.reserve(innerLEDs.size() + outerLEDs.size()); // preallocate memory
  allLEDs.insert(allLEDs.end(), innerLEDs.begin(), innerLEDs.end());
  allLEDs.insert(allLEDs.end(), outerLEDs.begin(), outerLEDs.end());

  if(allLEDs.size() != NUMBER_OF_LEDS) Serial.println("LED COUNT MISMATCH!");

	LEDStrip.Begin();
  LEDStrip.Show();
}
