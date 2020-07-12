#ifndef MAIN_HEADERS
#define MAIN_HEADERS

#include <NeoPixelBus.h>

struct ConfigurableSettings {
  bool on = true;

  int showId = 4;
  int showMode = 0;

  int hue = 64; // DEP
  int saturation = 255; // DEP
  int brightness = 255; // DEP

  HsbColor colour = HsbColor(0.5f, 1.0f, 1.0f);
};

extern ConfigurableSettings settings;

#endif
