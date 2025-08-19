#include <Adafruit_NeoPixel.h>
// 3 pins for stepper
// 1 pin for servo
// 1 pin for limit
// 1 pin for button
// 2 pins for RFID
// 2 pins for I2C time of flight and lux sensor
// 20 pins for Light strips (5 + 12 + 3)
// 18 PWM pins for spotlights
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (false) {
    while(!Serial) {
      delay(10);
    }

    while (1) {
      Serial.println(analogRead(A0));
      delay(20);
    }

  }
  if (false)
    testStepper();
  if (false) {
  digitalWrite(6, LOW);
  while (1) {
    delay(1000);
  }
  }
  if (false) {
    while (1) {
      for (int i = 0; i < 256; i++) {
        analogWrite(6, i);
        delay(20);
      }
      for (int i = 255; i >=0; i--) {
        analogWrite(6, i);
        delay(20);
      }
    }
  }
  setupLights();
  //setupStepper();
  Serial.println("Setup");
}

void loop() {
  // put your main code here, to run repeatedly:
  loopLights();
  //loopStepper();
  delay(1);
}

void toggleDoors() {
  stepperToggleDoors();
}

