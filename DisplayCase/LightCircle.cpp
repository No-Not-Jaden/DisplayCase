#include "LightCircle.h"
#include <math.h>

constexpr float lightMap[27][2] = {
  {2.5, 0}, {1.5, 0},
  {0.5, 0.83}, {1.5, 0.83}, {2.5, 0.83}, {3.5, 0.83},
  {4, 1.6}, {3, 1.6}, {2, 1.6}, {1, 1.6}, {0, 1.6},
  {0, 2.5}, {1, 2.5}, {2, 2.5}, {3, 2.5}, {4, 2.5},
  {4, 3.3}, {3, 3.3}, {2, 3.3}, {1, 3.3}, {0, 3.3},
  {0.5, 4.2}, {1.5, 4.2}, {2.5, 4.2}, {3.5, 4.2},
  {2.5, 5}, {1.5, 5}
};

LightCircle::LightCircle() : Light() {
  direction[0] = direction[1] = direction[2] = 0;
}

LightCircle::LightCircle(Adafruit_NeoPixel* stripRef, unsigned int startLED,
                         const float startPos[3], const float dir[3])
    : Light(stripRef, startLED, NUM_CIRCLE_LEDS, startPos) {
  direction[0] = dir[0];
  direction[1] = dir[1];
  direction[2] = dir[2];

  auto normalize = [](const float v[3], float out[3]) {
    float len = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    out[0] = v[0] / len;
    out[1] = v[1] / len;
    out[2] = v[2] / len;
  };

  auto cross = [](const float a[3], const float b[3], float out[3]) {
    out[0] = a[1]*b[2] - a[2]*b[1];
    out[1] = a[2]*b[0] - a[0]*b[2];
    out[2] = a[0]*b[1] - a[1]*b[0];
  };

  auto dot = [](const float a[3], const float b[3]) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
  };

  auto rotateVector = [](const float v[3], const float axis[3], float angle, float out[3]) {
    float c = cos(angle), s = sin(angle), one_c = 1 - c;
    float x = axis[0], y = axis[1], z = axis[2];

    float r[3][3] = {
      {c + x*x*one_c, x*y*one_c - z*s, x*z*one_c + y*s},
      {y*x*one_c + z*s, c + y*y*one_c, y*z*one_c - x*s},
      {z*x*one_c - y*s, z*y*one_c + x*s, c + z*z*one_c}
    };

    out[0] = r[0][0]*v[0] + r[0][1]*v[1] + r[0][2]*v[2];
    out[1] = r[1][0]*v[0] + r[1][1]*v[1] + r[1][2]*v[2];
    out[2] = r[2][0]*v[0] + r[2][1]*v[1] + r[2][2]*v[2];
  };

  float norm[3];
  normalize(direction, norm);

  float defaultNormal[3] = {0, 0, 1};
  float axis[3];
  cross(defaultNormal, norm, axis);

  float axisLen = sqrt(dot(axis, axis));
  float angle = acos(dot(defaultNormal, norm));

  if (axisLen > 1e-6) {
    normalize(axis, axis);
  } else {
    axis[0] = 1; axis[1] = 0; axis[2] = 0;
    angle = 0;
  }

  pixelPositions = new float[NUM_CIRCLE_LEDS][3];
  for (size_t i = 0; i < NUM_CIRCLE_LEDS; i++) {
    float local[3] = {lightMap[i][0], lightMap[i][1], 0};
    float rotated[3];
    rotateVector(local, axis, angle, rotated);

    pixelPositions[i][0] = startPos[0] + rotated[0];
    pixelPositions[i][1] = startPos[1] + rotated[1];
    pixelPositions[i][2] = startPos[2] + rotated[2];
  }
}
