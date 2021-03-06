#pragma SPARK_NO_PREPROCESSOR
#include <FastLED.h>
#include "flash.h"
#include "twinkles.h"

FASTLED_USING_NAMESPACE

STARTUP(WiFi.selectAntenna(ANT_AUTO));

#define NUM_LEDS    20
#define BRIGHTNESS  120
#define APPID       32

const TProgmemRGBPalette16 Snow_p =
{  0x404040, 0x404040, 0x404040, 0x404040,
   0x404040, 0x404040, 0x404040, 0x404040,
   0x404040, 0x404040, 0x404040, 0x404040,
   0x404040, 0x404040, 0x404040, 0xFFFFFF
};

CRGB strip[NUM_LEDS];
ChristmasFlash lights(strip, NUM_LEDS, BRIGHTNESS);
Twinkles twinkles(NUM_LEDS, strip, Snow_p);

int g_program;
int g_appid;
int g_state;

int setProgram(String p)
{
    g_program = p.toInt();

    if (g_program == 1 || g_program == 2) {
        EEPROM.put(0, g_program);
        Particle.publish("EEPROM", String::format("EEPROM Updated a value to %d", g_program), PRIVATE);
    }

    return g_program;
}

int setProgramBrightness(String b)
{
    int bright = b.toInt();

    if (bright > 0 && bright < 255) {
        lights.setBrightness(bright);
    }

    return bright;
}

int setProgramDensity(String d)
{
    int density = d.toInt();

    if (density > 0 && density <= 8) {
        twinkles.setDensity(density);
    }

    return density;
}

int setProgramSpeed(String s)
{
    int speed = s.toInt();

    if (speed > 0 && speed <= 8) {
        twinkles.setSpeed(speed);
    }

    return speed;
}

void setup()
{
    EEPROM.get(0, g_program);
    if (g_program == 0xffffffff) {
        g_program = 1;
        EEPROM.put(0, g_program);
        Particle.publish("EEPROM", String::format("EEPROM Updated a value to %d", g_program), PRIVATE);
    }
    g_appid = APPID;
    g_state = true;

    Particle.function("setProg", setProgram);
    Particle.function("setBright", setProgramBrightness);
    Particle.function("setDensity", setProgramDensity);
    Particle.function("setSpeed", setProgramSpeed);
    Particle.variable("id", g_appid);
    Particle.variable("program", g_program);

    delay(2000);

    FastLED.addLeds<NEOPIXEL, D2>(strip, NUM_LEDS);
}

void loop()
{
    switch (g_program) {
    case 0:
        if (g_state) {
            for (int i = 0; i < NUM_LEDS; i++) {
                strip[i] = CRGB::Black;
            }
            FastLED.show();
            g_state = false;
        }
        break;
    case 1:
        if (!g_state)
            g_state = true;
        lights.run();
        lights.seeTheRainbow();
        FastLED.show();
        delay(20);
        break;
    case 2:
        if (!g_state)
            g_state = true;
        twinkles.run();
        FastLED.show();
        break;
    }
}
