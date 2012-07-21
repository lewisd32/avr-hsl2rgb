This library converts hue/saturation/luminance values to red/green/blue values, suitable for controlling RGB LEDs.

Two different functions are included for this purpose.
One (hsl2rgb_orig) is very slightly modified code from Johngineer's blog: http://www.johngineer.com/blog/?p=1022
Variable names are changed, but it it otherwise identical.
The other (hsl2rgb) is an optimized version which produces *almost* identical output, but is 13x faster on an ATmega.

See hsl2rgb.cpp for more information.

Written by Derek Lewis, with code from "Johngineer".
MIT license, all text above must be included in any redistribution

To download. click the DOWNLOADS button in the top right corner, rename the uncompressed folder hsl2rgb.

Place the hsl2rgb library folder your <arduinosketchfolder>/libraries/ folder.  Create the libraries folder if it does not exist.  You'll need to restart the Arduino IDE for it to recognize the new library.

