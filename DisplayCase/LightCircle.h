// top lights are 2 4 5 5 5 4 2
//      1  0
//   2  3  4  5
// 10  9  8  7  6
// 11 12 13 14 15
// 20 19 18 17 16
//  21 22 23 24
//     26 25

#ifndef LIGHTCIRCLE_H
#define LIGHTCIRCLE_H
#include "Light.h"
#include <Adafruit_NeoPixel.h>
#define NUM_CIRCLE_LEDS 27
class LightCircle : public Light {
  private:
    float direction[3];
  public:
    LightCircle(Adafruit_NeoPixel* stripRef, unsigned int startLED, const float startPos[3], const float dir[3]);
    LightCircle();
};
#endif