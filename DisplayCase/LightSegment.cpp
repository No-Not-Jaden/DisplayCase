#include "LightSegment.h"
#include <stdlib.h>

LightSegment::LightSegment() : Light() {
  direction[0] = direction[1] = direction[2] = 0;
}

LightSegment::LightSegment(Adafruit_NeoPixel* stripRef, unsigned int startLED, unsigned int length,
                           const float startPos[3], const float dir[3])
    : Light(stripRef, startLED, length, startPos) {
  direction[0] = dir[0];
  direction[1] = dir[1];
  direction[2] = dir[2];

  pixelPositions = new float[length][3];
  for (size_t i = 0; i < length; i++) {
    pixelPositions[i][0] = startPos[0] + direction[0] * i;
    pixelPositions[i][1] = startPos[1] + direction[1] * i;
    pixelPositions[i][2] = startPos[2] + direction[2] * i;
  }
}




