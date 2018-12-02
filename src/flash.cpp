#include "flash.h"

static int ChristmasColorWheel[] = {
    HUE_BLUE,
    HUE_ORANGE,
    HUE_YELLOW,
    HUE_GREEN,
    HUE_AQUA,
    HUE_RED,
    HUE_PURPLE,
    HUE_PINK,
};

ChristmasFlash::ChristmasFlash(CRGB *strip, int count, int bright) :
    m_strip(strip), m_numPixels(count), m_brightness(bright), m_started(false)
{
    m_numColors = sizeof(ChristmasColorWheel);
    m_colors = new CHSV[m_numColors];
}

ChristmasFlash::~ChristmasFlash()
{
}

void ChristmasFlash::start()
{
    for (int i = 0; i < m_numPixels; i++) {
        m_colors[i].h = ChristmasColorWheel[random(0, m_numColors)];
        m_colors[i].v = m_brightness;
        m_colors[i].s = 255;
    }
    m_inAction = random(0, 20);
    m_fading = true;
    m_started = true;
}

void ChristmasFlash::run()
{
    if (!m_started) {
        start();
    }
    else {
        if (m_colors[m_inAction].v == 0) {
            m_fading = false;
            m_colors[m_inAction].h = ChristmasColorWheel[random(0, m_numColors)];
            m_colors[m_inAction].v++;
        }
        else if (m_fading && m_colors[m_inAction].s > 0) {
            m_colors[m_inAction].v--;
        }
        else if (m_colors[m_inAction].v < m_brightness && !m_fading) {
            m_colors[m_inAction].v++;
        }
        else if (m_colors[m_inAction].v == m_brightness && !m_fading) {
            m_fading = true;
            m_inAction = random(0, 20);
        }
    }
}

void ChristmasFlash::end()
{
    m_started = false;
}

void ChristmasFlash::seeTheRainbow()
{
    hsv2rgb_rainbow(m_colors, m_strip, m_numPixels);
}
