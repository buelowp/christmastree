#include <FastLED.h>
#include "flash.h"
#include "twinkles.h"

FASTLED_USING_NAMESPACE

#define NUM_LEDS    20
#define BRIGHTNESS  120
#define APPID       19

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

    if (g_program != 1)
        lights.end();

    return g_program;
}

void setup()
{
    delay(3000);

    g_program = 1;
    g_appid = APPID;

    Particle.function("setProg", setProgram);
    Particle.variable("id", g_appid);
    Particle.variable("program", g_program);

    FastLED.addLeds<NEOPIXEL, D0>(strip, NUM_LEDS);
    delay(100);
    lights.start();
    lights.seeTheRainbow();
    FastLED.show();
}

void loop()
{
    switch (g_program) {
    case 0:
        for (int i = 0; i < NUM_LEDS; i++) {
            strip[i] = CRGB::Black;
        }
        FastLED.show();
        break;
    case 1:
        lights.run();
        lights.seeTheRainbow();
        FastLED.show();
        delay(15);
        break;
    case 2:
        twinkles.run();
        FastLED.show();
        break;
    }
}
