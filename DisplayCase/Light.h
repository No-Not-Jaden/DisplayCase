#ifndef LIGHT_H
#define LIGHT_H
#include <array>
#include <vector>
#include <Adafruit_NeoPixel.h>
  class Light {
    private:
      Adafruit_NeoPixel* stripRef;
      unsigned int startLED;
      unsigned int length;
      float startPos[3];
      uint32_t addColor(uint32_t c1, uint32_t c2);
      uint32_t subColor(uint32_t c1, uint32_t c2);
      uint32_t combineColors(uint32_t existingColor, uint32_t newColor, int colorMode);
    protected:
      float (*pixelPositions)[3];
    public:
      Light(Adafruit_NeoPixel* stripRef, unsigned int startLED, unsigned int length, const float startPos[3]);
      Light();
      // light constructor for a point light for spotlights?
      void clear();
      void lightSphere(float start[3], float radius, uint32_t color, int colorMode);
      void lightColor(uint32_t color);
      void lightBox(float smallerPos[3], float largerPos[3], uint32_t color, int colorMode);

  };
#endif