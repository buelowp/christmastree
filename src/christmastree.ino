#include <FastLED>

#include "flash.h"
#define NUM_LEDS    20
#define BRIGHTNESS  120

CRGB strip[NUM_LEDS];
ChristmasFlash lights(strip, NUM_LEDS, BRIGHTNESS);

void setup()
{
    FastLED.addLeds<NEOPIXEL, D0>(strip, NUM_LEDS);
    lights.start();
    FastLED.show();
}

void loop()
{
    lights.run();
    lights.seeTheRainbow();
    FastLED.show();
    delay(10);
}
