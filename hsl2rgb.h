#ifndef _HSL2RGB_H_INCLUDED
#define _HSL2RGB_H_INCLUDED

#include <inttypes.h>

void hsl2rgb(uint16_t hue, uint8_t sat, uint8_t lum, uint8_t rgb[3]);
void hsl2rgb_orig(uint16_t hue, uint8_t sat, uint8_t lum, uint8_t rgb[3]);

#endif
