#pragma SPARK_NO_PREPROCESSOR
#include <FastLED.h>
#include "flash.h"
#include "twinkles.h"

FASTLED_USING_NAMESPACE

STARTUP(WiFi.selectAntenna(ANT_AUTO));

#define NUM_LEDS    25
#define BRIGHTNESS  125
#define APPID       35
#define PROG_ADDR   0
#define NUM_ADDR    4

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
int g_numLeds;

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

int setNumLeds(String c)
{
    int count = c.toInt();
    if (count == 0)
        return 0;
        
    g_numLeds = count;
    EEPROM.put(NUM_ADDR, g_numLeds);
    Particle.publish("LEDCOUNT", String::format("EEPROM Update num leds to %d", g_numLeds), PRIVATE);
    System.reset();
    return count;
}

void setup()
{
    EEPROM.get(PROG_ADDR, g_program);
    if (g_program == -1) {
        g_program = 1;
        EEPROM.put(PROG_ADDR, g_program);
        Particle.publish("EEPROM", String::format("EEPROM Updated program to %d", g_program), PRIVATE);
    }
    EEPROM.get(NUM_ADDR, g_numLeds);
    if (g_numLeds == -1) {
        g_numLeds = 20;
        EEPROM.put(NUM_ADDR, g_numLeds);
        Particle.publish("LEDCOUNT", String::format("EEPROM Update num leds to %d", g_numLeds), PRIVATE);
    }

    g_appid = APPID;
    g_state = true;

    lights.setNumLeds(g_numLeds);
    twinkles.setNumLeds(g_numLeds);

    Particle.function("setProg", setProgram);
    Particle.function("setBright", setProgramBrightness);
    Particle.function("setDensity", setProgramDensity);
    Particle.function("setSpeed", setProgramSpeed);
    Particle.function("setCount", setNumLeds);
    Particle.variable("id", g_appid);
    Particle.variable("count", g_numLeds);
    Particle.variable("program", g_program);

    delay(2000);

    FastLED.addLeds<NEOPIXEL, D6>(strip, g_numLeds);
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
