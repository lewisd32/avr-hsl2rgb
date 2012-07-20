#include <hsl2rgb.h>

/*

This example compares the performance of the old function to the performance
of the new function.

*/

void setup() {
  Serial.begin(9600);

  long start;
  long end;

  Serial.println("Testing empty loop");
  start = micros();
  for (uint16_t hue = 0; hue < 768; hue += 8) {
    for (uint16_t sat = 0; sat < 256; sat += 16) {
      for (uint16_t lum = 0; lum < 256; lum += 16) {
        uint8_t rgb[3];
      }
    }
  }
  end = micros();
  long duration_empty = end-start;
  Serial.println(duration_empty);
  
  Serial.println("Testing new hsl2rgb");
  start = micros();
  for (uint16_t hue = 0; hue < 768; hue += 8) {
    for (uint16_t sat = 0; sat < 256; sat += 16) {
      for (uint16_t lum = 0; lum < 256; lum += 16) {
        uint8_t rgb[3];

        hsl2rgb(hue, sat, lum, rgb);
      }
    }
  }
  end = micros();
  long duration_new = end-start;
  Serial.println(duration_new);
  
  Serial.println("Testing old hsl2rgb");
  start = micros();
  for (uint16_t hue = 0; hue < 768; hue += 8) {
    for (uint16_t sat = 0; sat < 256; sat += 16) {
      for (uint16_t lum = 0; lum < 256; lum += 16) {
        uint8_t rgb[3];

        hsl2rgb_orig(hue, sat, lum, rgb);
      }
    }
  }
  end = micros();
  long duration_old = end-start;
  Serial.println(duration_old);
  
  Serial.print("New is ");
  Serial.print( (float)duration_old/duration_new );
  Serial.println(" times faster than old.");
  
  Serial.println("Done testing.");
}


void loop() {
  // do nothing
}
