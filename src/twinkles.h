/*
 * Twinkles.h
 *
 *  Created on: Dec 17, 2015
 *      Author: pete
 */

#ifndef USER_APPLICATIONS_WINDOWLIGHTS_TWINKLES_H_
#define USER_APPLICATIONS_WINDOWLIGHTS_TWINKLES_H_

#include <FastLED.h>

FASTLED_USING_NAMESPACE

class Twinkles {
public:
	Twinkles(int, CRGB*, CRGBPalette16);
	virtual ~Twinkles();

	void start();
	void run();
	void setBackgroundColor(CRGB);
	void setDensity(int);
	void setSpeed(int);
	void setNumLeds(int n) { m_numLeds = n; }

private:
	uint8_t attackDecayWave8(uint8_t);
	CRGB computeOneTwinkle(uint32_t ms, uint8_t salt);

	CRGBPalette16 gCurrentPalette;
	CRGB gBackgroundColor;
    CRGB *strip;
    int m_numLeds;
    int m_density;
    int m_speed;
};

#endif /* USER_APPLICATIONS_WINDOWLIGHTS_TWINKLES_H_ */
