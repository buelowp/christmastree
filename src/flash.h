#ifndef __FLASH_H__
#define __FLASH_H__

#include <FastLED.h>

class ChristmasFlash
{
public:
    ChristmasFlash(CRGB*, int);
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
}
