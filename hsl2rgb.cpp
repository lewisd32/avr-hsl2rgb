#include "hsl2rgb.h"

/*
 * Original implementation by Johngineer.
 * From: http://www.johngineer.com/blog/?p=1022
 *
 * Optimized by Derek Lewis.
 * http://www.surprisingedge.com
 *
 * == Functional Differences ==
 *
 * Both implementations here treat saturation the reverse of the implementation
 * from Johngineer's blog.  Convention in all the graphics tools I've used is
 * that 0 saturation is greyscale, and 255 saturation is bright saturated
 * colours, so that's how it's been implemented here.
 *
 * Some comprimises were made in the new version in order to be able to do an
 * efficient divide by 256, instead of the slower divide by 255, so the exact
 * numeric output is slightly different, but never off by more than one.
 *
 * == Performance ==
 *
 * The new implementation is 13x faster on an ATmega328.
 * May not have as much benifit on an ATtiny, with the lack of the hardware
 * multiplier.
 *
 * == Size ==
 *
 * The hsl2rgb method adds only 152 bytes to the program.
 * The hsl2rgb_orig method adds 390 bytes.
 *
 * == Examples ==
 *
 * See the "test" example sketch for a series of tests that verify results
 * against the original algorithm.
 *
 * See the "perftest" example stetch for a comparison of performance.
 * 
 */


void hsl2rgb(uint16_t hue, uint8_t sat, uint8_t lum, uint8_t rgb[3]) {

	uint8_t inverse_sat = (sat ^ 255);

	uint8_t r_temp, g_temp, b_temp;
	uint8_t hue_mod;

	hue_mod = hue % 256; // same performance as hue & 0xff

	if (hue < 256) {
		r_temp = hue_mod ^ 255;
		g_temp = hue_mod;
		b_temp = 0;
	} else if (hue < 512) {
		r_temp = 0;
		g_temp = hue_mod ^ 255;
		b_temp = hue_mod;
	} else if (hue < 768) {
		r_temp = hue_mod;
		g_temp = 0;
		b_temp = hue_mod ^ 255;
	} else {
		r_temp = 0;
		g_temp = 0;
		b_temp = 0;
	}
	
	rgb[0] 	= r_temp;
	rgb[1]	= g_temp;
	rgb[2]	= b_temp;

	for (int i = 0; i < 3; ++i) {
		/*
		 * Original:
		 * rgb[i] = ((((rgb[i] * inverse_sat) / 255) + sat) * lum) / 255;
		 * Changed to:
		 * rgb[i] = ((((rgb[i] * (inverse_sat+1)) / 256) + sat) * (lum+1)) / 256;
		 * Produces slightly different output, but is much faster.
		 *
		 * Code below is functionally the same, but optimized to make better
		 * use of the ATmega's hardware multiplier.
		 *
		 */
		uint8_t t8 = rgb[i];

		uint16_t t16 = t8 * inverse_sat;
		t16 = t16 + t8; // Instead of * (inverse_sat+1)
		t8 = t16 / 256; // same performance as t16 >> 8
		t8 = t8 + sat;

		t16 = t8 * lum;
		t16 = t16 + t8; // Instead of * (lum+1)
		t8 = t16 / 256; // same performance as t16 >> 8

		rgb[i] = t8;

	}
}


void hsl2rgb_orig(uint16_t hue, uint8_t sat, uint8_t lum, uint8_t rgb[3]) {
	uint16_t r_temp, g_temp, b_temp;
	uint8_t hue_mod;
	uint8_t inverse_sat = (sat ^ 255);

	hue = hue % 768;
	hue_mod = hue % 256;

	if (hue < 256)
	{
		r_temp = hue_mod ^ 255;
		g_temp = hue_mod;
		b_temp = 0;
	}

	else if (hue < 512)
	{
		r_temp = 0;
		g_temp = hue_mod ^ 255;
		b_temp = hue_mod;
	}

	else if ( hue < 768)
	{
		r_temp = hue_mod;
		g_temp = 0;
		b_temp = hue_mod ^ 255;
	}

	else
	{
		r_temp = 0;
		g_temp = 0;
		b_temp = 0;
	}

	r_temp = ((r_temp * inverse_sat) / 255) + sat;
	g_temp = ((g_temp * inverse_sat) / 255) + sat;
	b_temp = ((b_temp * inverse_sat) / 255) + sat;

	r_temp = (r_temp * lum) / 255;
	g_temp = (g_temp * lum) / 255;
	b_temp = (b_temp * lum) / 255;

	rgb[0] 	= (uint8_t)r_temp;
	rgb[1]	= (uint8_t)g_temp;
	rgb[2]	= (uint8_t)b_temp;
}
