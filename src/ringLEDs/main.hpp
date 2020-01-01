#include <vector>

#include <NeoPixelBus.h>

struct RingLED {
    int index;
    float angle;
    int ring;
};

extern NeoPixelBus<NeoGrbFeature, NeoEsp8266Dma800KbpsMethod> LEDStrip;
// extern std::vector<RingLED> innerLEDs;
// extern std::vector<RingLED> outerLEDs;
extern int ringCount;
extern std::vector<RingLED> allLEDs;
extern void initialiseLEDs();
