#include <vector>

#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

enum Ring {inner, outer};

struct RingLED {
    int index;
    float angle;
    Ring ring;
};

extern CRGB rawLEDs[];
extern std::vector<RingLED> innerLEDs;
extern std::vector<RingLED> outerLEDs;
extern std::vector<RingLED> allLEDs;
extern void initialiseLEDs(int brightness);
