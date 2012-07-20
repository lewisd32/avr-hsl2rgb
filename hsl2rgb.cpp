#include "hsl2rgb.h"

void hsl2rgb(uint16_t hue, uint8_t rgb[3]) {

	uint16_t r_temp, g_temp, b_temp;
	uint16_t hue_mod;

	//hue = hue % 768;
	hue_mod = hue & 0xFF; // hue % 256

	if (hue < 256) {
		r_temp = hue_mod ^ 255;
		g_temp = hue_mod;
		b_temp = 0;
	} else if (hue < 512) {
		r_temp = 0;
		g_temp = hue_mod ^ 255;
		b_temp = hue_mod;
	} else if ( hue < 768) {
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
}

void hsl2rgb(uint16_t hue, uint8_t sat, uint8_t lum, uint8_t rgb[3]) {

	uint8_t inverse_sat = (sat ^ 255);

	hsl2rgb(hue, rgb);

	for (int i = 0; i < 3; ++i) {
		uint8_t t8 = rgb[i];

		uint16_t t16 = t8 * inverse_sat;
		t16 = t16 + t8; // * (inverse_sat+1)
		t8 = t16 >> 8;
		t8 = t8 + sat;

		t16 = t8 * lum;
		t16 = t16 + t8; // * (lum+1)
		t8 = t16 >> 8;

		rgb[i] = t8;

		//rgb[i] = ((((rgb[i] * inverse_sat) / 255) + sat) * lum) / 255;
		//rgb[i] = ((((rgb[i] * (inverse_sat+1)) / 256) + sat) * (lum+1)) / 256;
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
