/*
  Header for the L298N Motor Controllers
*/

#ifndef MOTOR_CONTROLLER_CPP
#define MOTOR_CONTROLLER_CPP

// Includes
#include "MotorController.h"

// ============================================================================
// MotorController - Constructor for the L298N Motor Controller wrapper class.
// ============================================================================
MotorController::MotorController(byte PIN_EN_1, byte PIN_EN_2, byte PIN_PWM) {

  // Assign class variables 
  this->PIN_EN_1 = PIN_EN_1;
  this->PIN_EN_2 = PIN_EN_2;
  this->PIN_PWM  = PIN_PWM;

  // After assigning the pins run setup
  setup();
}

// ==========================================================
// setup() - Configure the pin directions and default values
// ==========================================================
void MotorController::setup() {
  
  // Set the pin types
  pinMode(PIN_EN_1, OUTPUT);
  pinMode(PIN_EN_2, OUTPUT);
  pinMode(PIN_PWM,  OUTPUT);

  setDirection(STOPPED);

}

// ===============================================================
// setDirection - Updates the enable pins to reflect the movement
//                direction
// ===============================================================
void MotorController::setDirection(direction dir) {

  if (dir == FORWARD) {
    digitalWrite(PIN_EN_1, HIGH);
    digitalWrite(PIN_EN_2, LOW);
  } else if (dir == BACKWARD) {
    digitalWrite(PIN_EN_1, LOW);
    digitalWrite(PIN_EN_2, HIGH);
  } else { 
    digitalWrite(PIN_EN_1, LOW);  // Stopped direction.
    digitalWrite(PIN_EN_2, LOW);
  }

  // Update the current direction of the motor
  this->current_direction = dir;
}

#endif