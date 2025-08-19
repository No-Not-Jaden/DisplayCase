

#include <Adafruit_NeoPixel.h>
#include "LightSegment.h"
#include "LightCircle.h"

// LED count
#define LEFT_SEG_1 80
#define LEFT_SEG_2 20
#define LEFT_SEG_3 120
#define LEFT_SEG_4 20
#define LEFT_SEG_5 40

#define RIGHT_SEG_1 80
#define RIGHT_SEG_2 20
#define RIGHT_SEG_3 120
#define RIGHT_SEG_4 20
#define RIGHT_SEG_5 40

#define TOP_BACK_SEG 60
#define TOP_FRONT_SEG 60
#define BOTTOM_SEG 60

#define LEFT_STRIP_PIN 20
#define RIGHT_STRIP_PIN 21
#define TOP_BACK_STRIP_PIN 15
#define TOP_FRONT_STRIP_PIN 16
#define BOTTOM_STRIP_PIN 17

#define NUM_EXTERNAL_SEGMENTS 13

#define INTERNAL_STRIP_LENGTH 12

#define SPOTLIGHT_STRIP_LENGTH 27
#define LEFT_SPOTLIGHT_PIN 27
#define MIDDLE_SPOTLIGHT_PIN 28
#define RIGHT_SPOTLIGHT_PIN 29

#define BRIGHTNESS 30

// led pins 8-11 14-17 18-21 40-47 even&odd 48-51(square) 32,33,36,37

int ledPins[28] = {8, 9, 10, 11, 14, 15, 16, 17, 18, 19, 20, 21, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 32, 33, 36, 37};


Adafruit_NeoPixel leftStrip = Adafruit_NeoPixel(LEFT_SEG_1 + LEFT_SEG_2 + LEFT_SEG_3 + LEFT_SEG_4 + LEFT_SEG_5, ledPins[27], NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel rightStrip = Adafruit_NeoPixel(RIGHT_SEG_1 + RIGHT_SEG_2 + RIGHT_SEG_3 + RIGHT_SEG_4 + RIGHT_SEG_5, ledPins[26], NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel topBackStrip = Adafruit_NeoPixel(TOP_BACK_SEG, ledPins[25], NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel topFrontStrip = Adafruit_NeoPixel(TOP_FRONT_SEG, ledPins[24], NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel bottomStrip = Adafruit_NeoPixel(BOTTOM_SEG, ledPins[23], NEO_RGBW + NEO_KHZ800);
// one segment for each edge except the bottom back edge
// the 2 sides have one extra edge because the strip doesn't start in a corner
LightSegment externalSegments[NUM_EXTERNAL_SEGMENTS];


// like a phone kepad
LightSegment internalSegments[12];
Adafruit_NeoPixel internalStrips[12];

Adafruit_NeoPixel leftSpotlight = Adafruit_NeoPixel(SPOTLIGHT_STRIP_LENGTH, ledPins[22], NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel middleSpotlight = Adafruit_NeoPixel(SPOTLIGHT_STRIP_LENGTH, ledPins[21], NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel rightSpotlight = Adafruit_NeoPixel(SPOTLIGHT_STRIP_LENGTH, ledPins[20], NEO_RGBW + NEO_KHZ800);

LightCircle topLights[3];


// PWM pins for Spotlights
// D2-D9, D11, D13-D45, D48, D50-D53.
// Pin #2 has PWM Channel 0x002
// Pin #3 has PWM Channel 0x003
// Pin #4 has PWM Channel 0x004
// Pin #5 has PWM Channel 0x005
// Pin #6 has PWM Channel 0x100 8
// Pin #7 has PWM Channel 0x101
// Pin #8 has PWM Channel 0x100 6
// Pin #9 has PWM Channel 0xb00 14
// Pin #10 has PWM Channel 0xc00 12
// Pin #12 has PWM Channel 0xc00 10
// Pin #13 has PWM Channel 0xc01
// Pin #14 has PWM Channel 0xb00 9
// Pin #18 has PWM Channel 0x300
// Pin #19 has PWM Channel 0x301
// Pin #23 has PWM Channel 0x201
// Pin #24 has PWM Channel 0x001
// Pin #25 has PWM Channel 0x000
// Pin #26 has PWM Channel 0x700
// Pin #27 has PWM Channel 0x701
// Pin #28 has PWM Channel 0x200
// Pin #30 has PWM Channel 0x901
// Pin #31 has PWM Channel 0x900
// Pin #34 has PWM Channel 0x801
// Pin #35 has PWM Channel 0x800
// Pin #38 has PWM Channel 0x401
// Pin #39 has PWM Channel 0x400

// 2-7 23-28 30,31,34,35,38,39

// like a phone keypad
int spotlightPins[18] = {2, 3, 4, 5, 6, 7, 23, 24, 25, 26, 27, 28, 30, 31, 34, 35, 38, 39};



float pulsePosition;
float pulseSpeed = 0.01;
uint8_t pulseBrightnessMod = 2;

// internal specifications
const float colThickness = 20;
const float rowThickness = 25;
const float startZ = 1;
const float startY = LEFT_SEG_3 - 4 - rowThickness;
const float startX = 2;
const float stripThickness = 1;

// 0 = middle
// 1 = both
// 2 = outside
int litSections = 0;
void setupLights() {
  // pinMode?
  for (int i = 0; i < )
  // external segments

    float p0[3] = {0, LEFT_SEG_5, 0};
    float d0[3] = {0,1,0};
    externalSegments[0] = LightSegment(&leftStrip, 0, LEFT_SEG_1, p0, d0);

    float p1[3] = {0, LEFT_SEG_5 + LEFT_SEG_1, 0};
    float d1[3] = {1,0,0};
    externalSegments[1] = LightSegment(&leftStrip, LEFT_SEG_1, LEFT_SEG_2, p1, d1);

    float p2[3] = {LEFT_SEG_2, LEFT_SEG_5 + LEFT_SEG_1, 0};
    float d2[3] = {0,-1,0};
    externalSegments[2] = LightSegment(&leftStrip, LEFT_SEG_1 + LEFT_SEG_2, LEFT_SEG_3, p2, d2);

    float p3[3] = {LEFT_SEG_2, 0, 0};
    float d3[3] = {-1,0,0};
    externalSegments[3] = LightSegment(&leftStrip, LEFT_SEG_1 + LEFT_SEG_2 + LEFT_SEG_3, LEFT_SEG_4, p3, d3);

    float p4[3] = {0, 0, 0};
    float d4[3] = {0,1,0};
    externalSegments[4] = LightSegment(&leftStrip, LEFT_SEG_1 + LEFT_SEG_2 + LEFT_SEG_3 + LEFT_SEG_4, LEFT_SEG_5, p4, d4);
  

  
    float p5[3] = {0, RIGHT_SEG_5, 0};
    float d5[3] = {0,1,0};
    externalSegments[5] = LightSegment(&rightStrip, 0, RIGHT_SEG_1, p5, d5);

    float p6[3] = {0, RIGHT_SEG_5 + RIGHT_SEG_1, 0};
    float d6[3] = {1,0,0};
    externalSegments[6] = LightSegment(&rightStrip, RIGHT_SEG_1, RIGHT_SEG_2, p6, d6);

    float p7[3] = {RIGHT_SEG_2, RIGHT_SEG_5 + RIGHT_SEG_1, 0};
    float d7[3] = {0,-1,0};
    externalSegments[7] = LightSegment(&rightStrip, RIGHT_SEG_1 + RIGHT_SEG_2, RIGHT_SEG_3, p7, d7);

    float p8[3] = {RIGHT_SEG_2, 0, 0};
    float d8[3] = {-1,0,0};
    externalSegments[8] = LightSegment(&rightStrip, RIGHT_SEG_1 + RIGHT_SEG_2 + RIGHT_SEG_3, RIGHT_SEG_4, p8, d8);

    float p9[3] = {0, 0, 0};
    float d9[3] = {0,1,0};
    externalSegments[9] = LightSegment(&rightStrip, RIGHT_SEG_1 + RIGHT_SEG_2 + RIGHT_SEG_3 + RIGHT_SEG_4, RIGHT_SEG_5, p9, d9);
  

  
    float p10[3] = {0, LEFT_SEG_1 + LEFT_SEG_5, 0};
    float d10[3] = {0, 0, 1};
    externalSegments[10] = LightSegment(&topBackStrip, 0, TOP_BACK_SEG, p10, d10);

    float p11[3] = {LEFT_SEG_2, LEFT_SEG_1 + LEFT_SEG_5, 0};
    float d11[3] = {0, 0, 1};
    externalSegments[11] = LightSegment(&topFrontStrip, 0, TOP_FRONT_SEG, p11, d11);

    float p12[3] = {LEFT_SEG_2, 0, 0};
    float d12[3] = {0, 0, 1};
    externalSegments[12] = LightSegment(&bottomStrip, 0, BOTTOM_SEG, p12, d12);
  

  // internal segments

  for(int i = 0; i < 12; i++) {
    float y = startY - (i / 6) * rowThickness;
    float z = startZ + (i % 6) * colThickness;

    if (i % 2 == 1) {
      z += colThickness - stripThickness;
    }

    internalStrips[i] = Adafruit_NeoPixel(INTERNAL_STRIP_LENGTH, ledPins[i], NEO_RGBW + NEO_KHZ800);
    
    float pos[3] = {startX, y, z};
    float dir[3] = {1, 0, 0};
    internalSegments[i] = LightSegment(&internalStrips[i], 0, INTERNAL_STRIP_LENGTH, pos, dir);
  }

  // top lights
  {
    float pos0[3] = {LEFT_SEG_2 / 2, LEFT_SEG_3, 1 + colThickness / 2.0f};
    float dir[3] = {0,1,0};
    topLights[0] = LightCircle(&leftSpotlight, 0, pos0, dir);

    float pos1[3] = {LEFT_SEG_2 / 2, LEFT_SEG_3, 1 + 3 * colThickness / 2.0f};
    topLights[1] = LightCircle(&middleSpotlight, 0, pos1, dir);

    float pos2[3] = {LEFT_SEG_2 / 2, LEFT_SEG_3, 1 + 5 * colThickness / 2.0f};
    topLights[2] = LightCircle(&rightSpotlight, 0, pos2, dir);
  }

  leftStrip.begin();
  leftStrip.setBrightness(BRIGHTNESS);
  rightStrip.begin();
  rightStrip.setBrightness(BRIGHTNESS);
  topBackStrip.begin();
  topBackStrip.setBrightness(BRIGHTNESS);
  topFrontStrip.begin();
  topFrontStrip.setBrightness(BRIGHTNESS);
  bottomStrip.begin();
  bottomStrip.setBrightness(BRIGHTNESS);
  for (size_t i = 0; i < 12; i++) {
    internalStrips[i].begin();
    internalStrips[i].setBrightness(BRIGHTNESS);
  }
  leftSpotlight.begin();
  leftSpotlight.setBrightness(BRIGHTNESS);
  middleSpotlight.begin();
  middleSpotlight.setBrightness(BRIGHTNESS);
  rightSpotlight.begin();
  rightSpotlight.setBrightness(BRIGHTNESS);
}

unsigned long nextUpdate = 0;

void loopLights() {
  // update lights
  if (nextUpdate < millis()) {
    nextUpdate = millis() + 2000;
    lightSection(leftStrip.Color(0, 0, 0, 0));
    if (litSections == 0) {
      litSections = 2;
    } else {
      litSections = 0;
    }
    lightSection(leftStrip.Color(128, 32, 100, 10));
    showStrips();
  }
}

void showStrips() {
  leftStrip.show();
  rightStrip.show();
  topBackStrip.show();
  topFrontStrip.show();
  bottomStrip.show();
  for (size_t i = 0; i < 12; i++) {
    internalStrips[i].show();
  }
  leftSpotlight.show();
  middleSpotlight.show();
  rightSpotlight.show();
}

void colorSet(uint32_t c, uint8_t wait) { // From NeoPixel Library
  for(uint16_t i=0; i<leftStrip.numPixels(); i++) {
      leftStrip.setPixelColor(i, c);
  }
   leftStrip.show();
   delay(wait);
}

// Sets the brightness of all the spotlights in the currently active section
void setSpotlightSectionBrightness(uint8_t brightness) {
  if (litSections <= 1) {
    //middle
    analogWrite(spotlightPins[2], brightness);
    analogWrite(spotlightPins[3], brightness);
    analogWrite(spotlightPins[8], brightness);
    analogWrite(spotlightPins[9], brightness);
    analogWrite(spotlightPins[14], brightness);
    analogWrite(spotlightPins[15], brightness);
  } 
  if (litSections >= 1) {
    // outside
    analogWrite(spotlightPins[0], brightness);
    analogWrite(spotlightPins[1], brightness);
    analogWrite(spotlightPins[4], brightness);
    analogWrite(spotlightPins[5], brightness);
    analogWrite(spotlightPins[6], brightness);
    analogWrite(spotlightPins[7], brightness);
    analogWrite(spotlightPins[10], brightness);
    analogWrite(spotlightPins[11], brightness);
    analogWrite(spotlightPins[12], brightness);
    analogWrite(spotlightPins[13], brightness);
    analogWrite(spotlightPins[16], brightness);
    analogWrite(spotlightPins[17], brightness);
  }
}

void lightSection(uint32_t color) {
  if (litSections <= 1) {
    // middle
    topLights[1].lightColor(color);

    internalSegments[2].lightColor(color);
    internalSegments[3].lightColor(color);
    internalSegments[8].lightColor(color);
    internalSegments[9].lightColor(color);
  }
  if (litSections >= 1) {
    // outside
    topLights[0].lightColor(color);
    topLights[2].lightColor(color);

    internalSegments[0].lightColor(color);
    internalSegments[1].lightColor(color);
    internalSegments[4].lightColor(color);
    internalSegments[5].lightColor(color);
    internalSegments[6].lightColor(color);
    internalSegments[7].lightColor(color);
    internalSegments[10].lightColor(color);
    internalSegments[11].lightColor(color);
  }
}

void lightSphere(float start[3], float radius, uint32_t color, bool additive) {
  if (litSections <= 1) {
    // middle
    topLights[1].lightSphere(start, radius, color, additive);

    internalSegments[2].lightSphere(start, radius, color, additive);
    internalSegments[3].lightSphere(start, radius, color, additive);
    internalSegments[8].lightSphere(start, radius, color, additive);
    internalSegments[9].lightSphere(start, radius, color, additive);
  }
  if (litSections >= 1) {
    // outside
    topLights[0].lightSphere(start, radius, color, additive);
    topLights[2].lightSphere(start, radius, color, additive);

    internalSegments[0].lightSphere(start, radius, color, additive);
    internalSegments[1].lightSphere(start, radius, color, additive);
    internalSegments[4].lightSphere(start, radius, color, additive);
    internalSegments[5].lightSphere(start, radius, color, additive);
    internalSegments[6].lightSphere(start, radius, color, additive);
    internalSegments[7].lightSphere(start, radius, color, additive);
    internalSegments[10].lightSphere(start, radius, color, additive);
    internalSegments[11].lightSphere(start, radius, color, additive);
  }

  for (int i = 0; i < NUM_EXTERNAL_SEGMENTS; i++) {
    externalSegments[i].lightSphere(start, radius, color, additive);
  }
}

void getSpotlightLocation(int index, float pos[3]) {
  pos[0] = startX + INTERNAL_STRIP_LENGTH / 2;
  pos[1] = startY - rowThickness / 2 - rowThickness * ((int) index / 6);
  pos[2] = startZ + ((int) (index % 6) / 2) * colThickness - colThickness / 2 - 3 + (index % 2) * 6;
}

// Spotlights use PWM



