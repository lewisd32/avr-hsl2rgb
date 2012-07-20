#ifndef _HSL2RGB_H_INCLUDED
#define _HSL2RGB_H_INCLUDED

#include <inttypes.h>

// Convert HSL to RGB using the fast algorithm
void hsl2rgb(uint16_t hue, uint8_t sat, uint8_t lum, uint8_t rgb[3]);

// Convert HSL to RGB using the original algorithm
void hsl2rgb_orig(uint16_t hue, uint8_t sat, uint8_t lum, uint8_t rgb[3]);

#endif
