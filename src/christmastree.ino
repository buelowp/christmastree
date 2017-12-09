#include <FastLED.h>
#include "flash.h"
#include "twinkles.h"

#define NUM_LEDS    20
#define BRIGHTNESS  120
#define APPID       1

const TProgmemRGBPalette16 Snow_p =
{  0x404040, 0x404040, 0x404040, 0x404040,
   0x404040, 0x404040, 0x404040, 0x404040,
   0x404040, 0x404040, 0x404040, 0x404040,
   0x404040, 0x404040, 0x404040, 0xFFFFFF
};

CRGB strip[NUM_LEDS];
ChristmasFlash lights(strip, NUM_LEDS, BRIGHTNESS);
Twinkles twinkles(strip, Snow_p);

int g_program;
int g_appid;

int setProgram(String p)
{
    g_program = p.toInt();
    return g_program;
}

void setup()
{
    FastLED.addLeds<NEOPIXEL, D0>(strip, NUM_LEDS);
    lights.start();
    FastLED.show();

    g_program = 1;
    g_appid = APPID;

    Particle.function("setProg", setProgram);
    Particle.variable("id", g_appid);
    Particle.variable("program", g_program);
}

void loop()
{
    switch (g_program) {
    case 1:
        lights.run();
        lights.seeTheRainbow();
        FastLED.show();
        delay(10);
        break;
    case 2:
        twinkles.run();
        FastLED.show();
        break;
    }
}
