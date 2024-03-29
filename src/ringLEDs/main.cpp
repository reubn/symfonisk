#include "main.hpp"

#define DATA_PIN 2
#define NUMBER_OF_LEDS 80

NeoPixelBus<NeoGrbFeature, NeoEsp8266Dma800KbpsMethod> LEDStrip(NUMBER_OF_LEDS, DATA_PIN); // Data Pin is ignored as RX is always used

int ringCount = 8;

//	Generated w/
// (({x, y}) => `std::vector<RingLED> allLEDs {
//     {${Array.from({length: x} , (_ , i) => Array.from({length: y} , (_ , j) => [(i * y) + j, (i / x).toFixed(1), !!(i % 2) ? j : y - j - 1].join(', ')).join('}, {')).join('},\n    {')}}
// };`)({x: 5, y: 16})
std::vector<RingLED> allLEDs {
     {0, 0.0, 7}, {1, 0.0, 6}, {2, 0.0, 5}, {3, 0.0, 4}, {4, 0.0, 3}, {5, 0.0, 2}, {6, 0.0, 1}, {7, 0.0, 0},
    {8, 0.1, 0}, {9, 0.1, 1}, {10, 0.1, 2}, {11, 0.1, 3}, {12, 0.1, 4}, {13, 0.1, 5}, {14, 0.1, 6}, {15, 0.1, 7},
    {16, 0.2, 7}, {17, 0.2, 6}, {18, 0.2, 5}, {19, 0.2, 4}, {20, 0.2, 3}, {21, 0.2, 2}, {22, 0.2, 1}, {23, 0.2, 0},
    {24, 0.3, 0}, {25, 0.3, 1}, {26, 0.3, 2}, {27, 0.3, 3}, {28, 0.3, 4}, {29, 0.3, 5}, {30, 0.3, 6}, {31, 0.3, 7},
    {32, 0.4, 7}, {33, 0.4, 6}, {34, 0.4, 5}, {35, 0.4, 4}, {36, 0.4, 3}, {37, 0.4, 2}, {38, 0.4, 1}, {39, 0.4, 0},
    {40, 0.5, 0}, {41, 0.5, 1}, {42, 0.5, 2}, {43, 0.5, 3}, {44, 0.5, 4}, {45, 0.5, 5}, {46, 0.5, 6}, {47, 0.5, 7},
    {48, 0.6, 7}, {49, 0.6, 6}, {50, 0.6, 5}, {51, 0.6, 4}, {52, 0.6, 3}, {53, 0.6, 2}, {54, 0.6, 1}, {55, 0.6, 0},
    {56, 0.7, 0}, {57, 0.7, 1}, {58, 0.7, 2}, {59, 0.7, 3}, {60, 0.7, 4}, {61, 0.7, 5}, {62, 0.7, 6}, {63, 0.7, 7},
    {64, 0.8, 7}, {65, 0.8, 6}, {66, 0.8, 5}, {67, 0.8, 4}, {68, 0.8, 3}, {69, 0.8, 2}, {70, 0.8, 1}, {71, 0.8, 0},
    {72, 0.9, 0}, {73, 0.9, 1}, {74, 0.9, 2}, {75, 0.9, 3}, {76, 0.9, 4}, {77, 0.9, 5}, {78, 0.9, 6}, {79, 0.9, 7}
};


void initialiseLEDs(){
  if(allLEDs.size() != NUMBER_OF_LEDS) Serial.println("LED COUNT MISMATCH!");

	LEDStrip.Begin();
  LEDStrip.Show();
}
