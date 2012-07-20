#include <hsl2rgb.h>

/*

This example verifies that both the old and the new functions return the same values
(give or take 1) over a wide range of inputs.
The results for some specific input values are verified for the new function as well.

If there is no numeric output, just a few lines of text, everything is working great.
Any discrepencies between the old and new functions, or between the expected and actual
results will be output.

*/

// Change allowable_difference to 0 to see how the results of the new algorithm differ
// from the original.
const uint8_t allowable_difference = 1;

void setup() {
  Serial.begin(9600);

  // hue is 0 to 767
  // red = 0
  // yellow = 127
  // green = 255
  // teal = 383
  // blue = 127
  // purple = 639

  Serial.println("Testing new implementation");

  // Test a bunch of specific values

  test(9, 255, 255, 255, 255, 255); // white
  test(90, 255, 255, 255, 255, 255); // white
  test(600, 255, 255, 255, 255, 255); // white

  test(9, 255, 0, 0, 0, 0); // black
  test(90, 255, 0, 0, 0, 0); // black
  test(600, 255, 0, 0, 0, 0); // black

  test(9, 255, 90, 90, 90, 90); // dark grey
  test(90, 255, 150, 150, 150, 150); // medium grey
  test(600, 255, 200, 200, 200, 200); // light grey

  test(0, 0, 255, 255, 0, 0); // bright red
  test(63, 0, 255, 192, 63, 0); // bright orange
  test(127, 0, 255, 128, 127, 0); // bright yellow
  test(191, 0, 255, 64, 191, 0); // bright yellow-green
  test(255, 0, 255, 0, 255, 0); // bright green
  test(319, 0, 255, 0, 192, 63); // bright green-teal
  test(383, 0, 255, 0, 128, 127); // bright teal
  test(447, 0, 255, 0, 64, 191); // bright teal-blue
  test(511, 0, 255, 0, 0, 255); // bright blue
  test(575, 0, 255, 63, 0, 192); // bright blue-purple
  test(639, 0, 255, 127, 0, 128); // bright purple
  test(703, 0, 255, 191, 0, 64); // bright purple-red


  test(0, 128, 255, 255, 128, 128); // semi-saturated red
  test(63, 128, 255, 224, 159, 128); // semi-saturated orange
  test(127, 128, 255, 192, 191, 128); // semi-saturated yellow
  test(191, 128, 255, 160, 223, 128); // semi-saturated yellow-green
  test(255, 128, 255, 128, 255, 128); // semi-saturated green
  test(319, 128, 255, 128, 224, 159); // semi-saturated green-teal
  test(383, 128, 255, 128, 192, 191); // semi-saturated teal
  test(447, 128, 255, 128, 160, 223); // semi-saturated teal-blue
  test(511, 128, 255, 128, 128, 255); // semi-saturated blue
  test(575, 128, 255, 159, 128, 224); // semi-saturated blue-purple
  test(639, 128, 255, 191, 128, 192); // semi-saturated purple
  test(703, 128, 255, 223, 128, 160); // semi-saturated purple-red

  test(0, 0, 128, 128, 0, 0); // dim red
  test(63, 0, 128, 96, 31, 0); // dim orange
  test(127, 0, 128, 64, 63, 0); // dim yellow
  test(191, 0, 128, 32, 96, 0); // dim yellow-green
  test(255, 0, 128, 0, 128, 0); // dim green
  test(319, 0, 128, 0, 96, 31); // dim green-teal
  test(383, 0, 128, 0, 64, 63); // dim teal
  test(447, 0, 128, 0, 32, 96); // dim teal-blue
  test(511, 0, 128, 0, 0, 128); // dim blue
  test(575, 0, 128, 31, 0, 96); // dim blue-purple
  test(639, 0, 128, 63, 0, 64); // dim purple
  test(703, 0, 128, 96, 0, 32); // dim purple-red

  test(0, 128, 128, 128, 64, 64); // dim semi-saturated red
  test(63, 128, 128, 112, 80, 64); // dim semi-saturated orange
  test(127, 128, 128, 96, 96, 64); // dim semi-saturated yellow
  test(191, 128, 128, 80, 112, 64); // dim semi-saturated yellow-green
  test(255, 128, 128, 64, 128, 64); // dim semi-saturated green
  test(319, 128, 128, 64, 112, 80); // dim semi-saturated green-teal
  test(383, 128, 128, 64, 96, 96); // dim semi-saturated teal
  test(447, 128, 128, 64, 80, 112); // dim semi-saturated teal-blue
  test(511, 128, 128, 64, 64, 128); // dim semi-saturated blue
  test(575, 128, 128, 80, 64, 112); // dim semi-saturated blue-purple
  test(639, 128, 128, 96, 64, 96); // dim semi-saturated purple
  test(703, 128, 128, 112, 64, 80); // dim semi-saturated purple-red


  Serial.println("Comparison testing both implementations");

  for (uint16_t hue = 0; hue < 768; hue += 16) {
    for (uint16_t sat = 0; sat < 256; sat += 16) {
      for (uint16_t lum = 0; lum < 256; lum += 16) {
        uint8_t rgb_old[3];
        uint8_t rgb_new[3];

        hsl2rgb_orig(hue, sat, lum, rgb_old);
        hsl2rgb(hue, sat, lum, rgb_new);

        check_close(hue, sat, lum, rgb_old[0], rgb_old[1], rgb_old[2], rgb_new);
      }
    }
  }

  Serial.println("Done testing.");
}

void test(uint16_t hue, uint8_t sat, uint8_t lum, uint8_t r, uint8_t g, uint8_t b) {
  uint8_t rgb[3];

  hsl2rgb(hue, sat, lum, rgb);

  check_close(hue, sat, lum, r, g, b, rgb);
}

void check(uint16_t hue, uint8_t sat, uint8_t lum, uint8_t r, uint8_t g, uint8_t b, uint8_t rgb[3]) {
  if (rgb[0] != r || rgb[1] != g || rgb[2] != b) {
    print(hue, sat, lum, r, g, b, rgb);
  }
}

void check_close(uint16_t hue, uint8_t sat, uint8_t lum, uint8_t r, uint8_t g, uint8_t b, uint8_t rgb[3]) {
  if (diff(rgb[0], r) > allowable_difference
    || diff(rgb[1], g) > allowable_difference
    || diff(rgb[2], b) > allowable_difference) {
    print(hue, sat, lum, r, g, b, rgb);
  }
}

uint8_t diff(uint8_t a, uint8_t b) {
  if (a > b) {
    return a - b;
  } 
  else {
    return b - a;
  }
}

void print(uint16_t hue, uint8_t sat, uint8_t lum, uint8_t r, uint8_t g, uint8_t b, uint8_t rgb[3]) {
  Serial.println("------------------------------------");
  Serial.print("Input   : ");
  Serial.print(hue);
  Serial.print(',');
  Serial.print(sat);
  Serial.print(',');
  Serial.println(lum);
  Serial.print("Expected: ");
  Serial.print(r);
  Serial.print(',');
  Serial.print(g);
  Serial.print(',');
  Serial.println(b);
  Serial.print("Actual  : ");
  Serial.print(rgb[0]);
  Serial.print(',');
  Serial.print(rgb[1]);
  Serial.print(',');
  Serial.println(rgb[2]);
}

void loop() {
  // do nothing
}


