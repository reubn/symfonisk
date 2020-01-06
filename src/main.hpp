#include <NeoPixelBus.h>

struct ConfigurableSettings {
  bool enabled = true;

  int showId = 0;
  int showMode = 0;

  int hue = 64; // DEP
  int saturation = 255; // DEP
  int brightness = 255; // DEP

  HsbColor colour = HsbColor(0.5f, 1.0f, 1.0f);
};
