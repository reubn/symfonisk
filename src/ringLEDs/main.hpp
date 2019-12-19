#include <vector>

#include <NeoPixelBus.h>

enum Ring {inner, outer};

struct RingLED {
    int index;
    float angle;
    Ring ring;
};

extern NeoPixelBus<NeoGrbFeature, NeoEsp8266Dma800KbpsMethod> LEDStrip;
extern std::vector<RingLED> innerLEDs;
extern std::vector<RingLED> outerLEDs;
extern std::vector<RingLED> allLEDs;
extern void initialiseLEDs();
