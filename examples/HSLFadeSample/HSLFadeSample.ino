/*
  This example shows how to fade an RGB LED through the hues, using the hsl2rgb library.
  
  The circuit:
  * RGB LED red lead to digital pin 9
  * RGB LED green lead to digital pin 10
  * RGB LED blue lead to digital pin 11
  For a common-cathode RGB LED:
  * RGB LED ground lead to ground pin
  For a common-anode RGB LED: (Change the commonCathode variable below)
  * RGB LED ground lead to +5V pin

*/

#include <hsl2rgb.h>

// If the common pin of the LED is connected to ground, then it is common cathode.
const boolean commonCathode = true;

const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

uint8_t rgb[3];

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  
  // Cycle once through the hues, from red, to green, to blue, back to red.
  for (int hue = 0; hue < 768; ++hue) {
    hsl2rgb(hue, 255, 255, rgb);
    writeLED(rgb);
    delay(10);
  }

  // Turn off the LED and pause for a moment.
  blackOut();

  // Cycle once through the primary colours, red, green and blue. (0, 256, and 512)
  for (int hue = 0; hue < 768; hue += 256) {
    // Fade from white to the primary colour.
    for (int saturation = 0; saturation < 255; ++saturation) {
      hsl2rgb(hue, saturation, 255, rgb);
      writeLED(rgb);
      delay(10);
    }
    
    // Pause at the primary colour for a moment.
    delay(500);
    
    // Fade from the primary colour back to white.
    for (int saturation = 255; saturation >= 0; --saturation) {
      hsl2rgb(hue, saturation, 255, rgb);
      writeLED(rgb);
      delay(10);
    }
    
    // Pause at white for a moment.
    delay(500);
  }

  // Turn off the LED and pause for a moment.
  blackOut();
}

void blackOut() {
  rgb[0] = rgb[1] = rgb[2] = 0;
  writeLED(rgb);
  delay(500);
}

void writeLED(uint8_t rgb[3]) {
    if (commonCathode) {
      // For common cathode LEDs, 0 is off and 255 is solid on.
      analogWrite(9, rgb[0]);
      analogWrite(10, rgb[1]);
      analogWrite(11, rgb[2]);
    } else {
      // For common anode, 0 is solid on, and 255 is off.
      analogWrite(9, rgb[0] ^ -1);
      analogWrite(10, rgb[1] ^ -1);
      analogWrite(11, rgb[2] ^ -1);
    }
}


