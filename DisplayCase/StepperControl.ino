#include <AccelStepper.h>

#define END_POSITION 20000
#define CLOSE_OFFSET 100

const int dirPin = 2;
const int stepPin = 3;
const int limitPin = 4;
const int direction = 1; // positive movement is away from home
enum class StepperState {
  FLOATING,
  HOMING,
  OPEN,
  OPENING,
  CLOSED,
  CLOSING
};
StepperState stepperState = StepperState::FLOATING;

#define motorInterfaceType 1

AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

void setupStepper() {
  myStepper.setMaxSpeed(2500);
  
}

void loopStepper() {
  switch (stepperState) {
    case StepperState::HOMING:
      loopHome();
      break;
    case StepperState::OPENING:
    case StepperState::CLOSING:
      loopMovement();
      break;
  }
}

void testStepper() {
  myStepper.setMaxSpeed(5000);
  myStepper.setSpeed(200);
  myStepper.setAcceleration(500);
  myStepper.moveTo(200000);
  while (1) {
      if (myStepper.distanceToGo() != 0) {
        myStepper.run();
      } else {
        myStepper.moveTo(-1 * myStepper.currentPosition());
      }
  }
}

// closing or opening
void loopMovement() {
  if (myStepper.distanceToGo() != 0) {
    myStepper.run();
  } else {
    if (stepperState == StepperState::CLOSING) {
      // home stepper to closed position
      loopHome();
    } else if (stepperState == StepperState::OPENING) {
      stepperState = StepperState::OPEN;
    }
  }
}

void loopHome() {
  if (stepperState != StepperState::HOMING) {
    myStepper.setAcceleration(0);
    myStepper.setSpeed(200);
    stepperState = StepperState::HOMING;
    if (digitalRead(limitPin) == HIGH) {
      // already activating limit move out a tiny bit
      myStepper.move(100 * direction);
    }
  }
  if (myStepper.distanceToGo() == 0) {
    // at destination
    if (digitalRead(limitPin) == LOW) {
      // have not hit the limit yet
      myStepper.move(-1 * direction);
      myStepper.runSpeed();
    } else {
      // at home
      stepperState = StepperState::CLOSED;
      // reset stepper location
      myStepper.moveTo(0);
      myStepper.setCurrentPosition(0);
    }
    if (myStepper.currentPosition() < -1 * END_POSITION) {
      Serial.println("Stepper moved too far to try and home.");
      while (1) {
        delay(10);
      }
    }
  } else {
    myStepper.runSpeed(); // no acceleration
  }
  
}

void stepperToggleDoors() {
  if (stepperState == StepperState::HOMING) {
    // don't interrupt homing
    return;
  }
  myStepper.setAcceleration(500);
  myStepper.setSpeed(200);
  if (stepperState == StepperState::FLOATING) {
    loopHome();
  } else if (stepperState == StepperState::OPEN || stepperState == StepperState::OPENING) {
    myStepper.moveTo(direction * CLOSE_OFFSET);
    stepperState = StepperState::CLOSING;
  } else if (stepperState == StepperState::CLOSED || stepperState == StepperState::CLOSING) {
    myStepper.moveTo(direction * END_POSITION);
    stepperState = StepperState::OPENING;
  }
}

