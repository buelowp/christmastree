#ifndef __FLASH_H__
#define __FLASH_H__

#include <FastLED.h>

FASTLED_USING_NAMESPACE

class ChristmasFlash
{
public:
    ChristmasFlash(CRGB*, int, int);
    ~ChristmasFlash();

    void start();
    void run();
    void end();
    void seeTheRainbow();

private:
    CRGB *m_strip;
    CHSV *m_colors;
    int m_numPixels;
    int m_numColors;
    int m_inAction;
    int m_brightness;
    bool m_fading;
    bool m_started;
};

#endif
