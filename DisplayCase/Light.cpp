#include "Light.h"
#include <math.h>   // for sqrt, pow
#include <algorithm> // for std::min

Light::Light(Adafruit_NeoPixel* stripRef, unsigned int startLED, unsigned int length, const float startPos[3])
    : stripRef(stripRef), startLED(startLED), length(length) {
  this->startPos[0] = startPos[0];
  this->startPos[1] = startPos[1];
  this->startPos[2] = startPos[2];

  // Optionally allocate pixelPositions here if needed
  // pixelPositions = new float[length][3];
}

Light::Light() : stripRef(NULL), startLED(0), length(0) {
  startPos[0] = startPos[1] = startPos[2] = 0;
}

void Light::clear() {
  for (size_t i = startLED; i < startLED + length; i++) {
    stripRef->setPixelColor(i, stripRef->Color(0,0,0,0));
  }
}

uint32_t Light::combineColors(uint32_t existingColor, uint32_t newColor, int colorMode) {
  if (colorMode == 1) {
    return addColor(existingColor, newColor);
  }
  if (colorMode == 2) {
    return subColor(existingColor, newColor);
  }
  return newColor;
}

void Light::lightSphere(float start[3], float radius, uint32_t color, int colorMode) {
  for (size_t i = 0; i < length; i++) {
    float* pos = pixelPositions[i];
    float dx = start[0] - pos[0];
    float dy = start[1] - pos[1];
    float dz = start[2] - pos[2];
    float distance = sqrt(dx*dx + dy*dy + dz*dz);

    if (distance < radius) {
      uint32_t existing = stripRef->getPixelColor(startLED + i);
      
      stripRef->setPixelColor(startLED + i, combineColors(existing, color, colorMode));
    }
  }
}

void Light::lightBox(float smallerPos[3], float largerPos[3], uint32_t color, int colorMode) {
  for (size_t i = 0; i < length; i++) {
    float* pos = pixelPositions[i];

    if (pos[0] > smallerPos[0] && pos[0] < largerPos[0] && pos[1] > smallerPos[1] && pos[1] < largerPos[1] && pos[2] > smallerPos[2] && pos[2] < largerPos[2]) {
      uint32_t existing = stripRef->getPixelColor(startLED + i);
      stripRef->setPixelColor(startLED + i, combineColors(existing, color, colorMode));
    }
  }
}

uint32_t Light::addColor(uint32_t c1, uint32_t c2) {
  uint8_t w1 = (c1 >> 24) & 0xFF;
  uint8_t r1 = (c1 >> 16) & 0xFF;
  uint8_t g1 = (c1 >> 8) & 0xFF;
  uint8_t b1 = c1 & 0xFF;

  uint8_t w2 = (c2 >> 24) & 0xFF;
  uint8_t r2 = (c2 >> 16) & 0xFF;
  uint8_t g2 = (c2 >> 8) & 0xFF;
  uint8_t b2 = c2 & 0xFF;

  uint8_t w = std::min(255, w1 + w2);
  uint8_t r = std::min(255, r1 + r2);
  uint8_t g = std::min(255, g1 + g2);
  uint8_t b = std::min(255, b1 + b2);

  return stripRef->Color(r, g, b, w);
}

uint32_t Light::subColor(uint32_t c1, uint32_t c2) {
  uint8_t w1 = (c1 >> 24) & 0xFF;
  uint8_t r1 = (c1 >> 16) & 0xFF;
  uint8_t g1 = (c1 >> 8) & 0xFF;
  uint8_t b1 = c1 & 0xFF;

  uint8_t w2 = (c2 >> 24) & 0xFF;
  uint8_t r2 = (c2 >> 16) & 0xFF;
  uint8_t g2 = (c2 >> 8) & 0xFF;
  uint8_t b2 = c2 & 0xFF;

  uint8_t w = std::max(0, w1 - w2);
  uint8_t r = std::max(0, r1 - r2);
  uint8_t g = std::max(0, g1 - g2);
  uint8_t b = std::max(0, b1 - b2);

  return stripRef->Color(r, g, b, w);
}

void Light::lightColor(uint32_t color) {
  for (size_t i = 0; i < length; i++) {
    stripRef->setPixelColor(startLED + i, color);
  }
}
