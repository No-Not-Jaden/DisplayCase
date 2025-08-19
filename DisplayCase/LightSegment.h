#ifndef LIGHTSEGMENT_H
#define LIGHTSEGMENT_H
#include <Adafruit_NeoPixel.h>
#include "Light.h"
class LightSegment : public Light {
  private:
    float direction[3];
  public:
    LightSegment(Adafruit_NeoPixel* stripRef, unsigned int startLED, unsigned int length, const float startPos[3], const float dir[3]);
    LightSegment();
};
#endif