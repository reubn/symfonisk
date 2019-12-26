#include "main.hpp"

#define DATA_PIN 2
#define NUMBER_OF_LEDS 80

NeoPixelBus<NeoGrbFeature, NeoEsp8266Dma800KbpsMethod> LEDStrip(NUMBER_OF_LEDS, DATA_PIN); // Data Pin is ignored as RX is always used

// 12 + 8 Concentric Rings
// std::vector<RingLED> outerLEDs {
// 	{0, 0.917, outer}, {1, 0, outer}, {2, 0.083, outer}, {3, 0.167, outer}, {4, 0.25, outer}, {5, 0.333, outer}, {6, 0.417, outer}, {7, 0.5, outer}, {8, 0.583, outer}, {9, 0.667, outer}, {10, 0.75, outer}, {11, 0.833, outer}
// };
//
// std::vector<RingLED> innerLEDs {
// 	{12, 0.125, inner}, {13, 0.25, inner}, {14, 0.375, inner}, {15, 0.5, inner}, {16, 0.625, inner}, {17, 0.75, inner}, {18, 0.875, inner}, {19, 0, inner}
// };

// std::vector<RingLED> outerLEDs {
// 	{0, 0, outer}, {1, 0.125, outer}, {2, 0.25, outer}, {3, 0.375, outer}, {4, 0.5, outer}, {5, 0.625, outer}, {6, 0.75, outer}, {7, 1, outer},
// 	// {8, 0, outer}, {9, 0.125, outer}, {10, 0.25, outer}, {11, 0.375, outer}, {12, 0.5, outer}, {13, 0.625, outer}, {14, 0.75, outer}, {15, 1, outer}
// };

std::vector<RingLED> outerLEDs {
	{0, 0, outer}, {1, 0, outer}, {2, 0, outer}, {3, 0, outer}, {4, 0, outer}, {5, 0, outer}, {6, 0, outer}, {7, 0, outer}, {8, 0, outer}, {9, 0, outer}, {10, 0, outer}, {11, 0, outer}, {12, 0, outer}, {13, 0, outer}, {14, 0, outer}, {15, 0, outer}, {16, 0, outer}, {17, 0, outer}, {18, 0, outer}, {19, 0, outer},
{20, 0.125, outer}, {21, 0.125, outer}, {22, 0.125, outer}, {23, 0.125, outer}, {24, 0.125, outer}, {25, 0.125, outer}, {26, 0.125, outer}, {27, 0.125, outer}, {28, 0.125, outer}, {29, 0.125, outer}, {30, 0.125, outer}, {31, 0.125, outer}, {32, 0.125, outer}, {33, 0.125, outer}, {34, 0.125, outer}, {35, 0.125, outer}, {36, 0.125, outer}, {37, 0.125, outer}, {38, 0.125, outer}, {39, 0.125, outer},
{40, 0.25, outer}, {41, 0.25, outer}, {42, 0.25, outer}, {43, 0.25, outer}, {44, 0.25, outer}, {45, 0.25, outer}, {46, 0.25, outer}, {47, 0.25, outer}, {48, 0.25, outer}, {49, 0.25, outer}, {50, 0.25, outer}, {51, 0.25, outer}, {52, 0.25, outer}, {53, 0.25, outer}, {54, 0.25, outer}, {55, 0.25, outer}, {56, 0.25, outer}, {57, 0.25, outer}, {58, 0.25, outer}, {59, 0.25, outer},
{60, 0.375, outer}, {61, 0.375, outer}, {62, 0.375, outer}, {63, 0.375, outer}, {64, 0.375, outer}, {65, 0.375, outer}, {66, 0.375, outer}, {67, 0.375, outer}, {68, 0.375, outer}, {69, 0.375, outer}, {70, 0.375, outer}, {71, 0.375, outer}, {72, 0.375, outer}, {73, 0.375, outer}, {74, 0.375, outer}, {75, 0.375, outer}, {76, 0.375, outer}, {77, 0.375, outer}, {78, 0.375, outer}, {79, 0.375, outer}
};

std::vector<RingLED> innerLEDs {};

std::vector<RingLED> allLEDs;

void initialiseLEDs(){
  allLEDs.reserve(innerLEDs.size() + outerLEDs.size()); // preallocate memory
  allLEDs.insert(allLEDs.end(), innerLEDs.begin(), innerLEDs.end());
  allLEDs.insert(allLEDs.end(), outerLEDs.begin(), outerLEDs.end());

  if(allLEDs.size() != NUMBER_OF_LEDS) Serial.println("LED COUNT MISMATCH!");

	LEDStrip.Begin();
  LEDStrip.Show();
}
