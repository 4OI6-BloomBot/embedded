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
  setPIN(PIN_EN_1, PIN_EN_2, PIN_PWM);

  // After assigning the pins run setup
  setup();
}

MotorController::MotorController() {
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

  // Disable voltage limit by default
  setVoltageLimit(CONTROLLER_INPUT_VOLTAGE);

  // Disable motor and set speed to 0 by default
  setDirection(STOPPED);
  setPower(0.0);

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


// ================================================================
// setPower - Sets the output power of the motor controller using
//            PWM. Input is a value from 0 to 1 that represents an
//            output voltage from 0 to voltage_limit.
// ================================================================
void MotorController::setPower(float power) {

  // Guard from setting a value above 1 which could
  // push the output voltage above the set limit.
  if (power > 1.0) return;

  // Calculate the ratio between the input voltage and the limit
  float limit_to_input_ratio = float(voltage_limit)/float(CONTROLLER_INPUT_VOLTAGE);

  // PWM output ranges from 0 --> 255. Therefore multiply by the 
  // power level (0 --> 1) and the input/limit ratio.
  byte pwm_code = 255 * power * limit_to_input_ratio;

  // Write the PWM code to the controller and update the stored value
  analogWrite(PIN_PWM, pwm_code);
  this->power = power;
}


// ===============================================================
// setVoltageLimit - Takes an input voltage and configures the 
//                   maximum output voltage from the controller.
// ===============================================================
void MotorController::setVoltageLimit(byte voltage) {
  if (voltage <= CONTROLLER_INPUT_VOLTAGE) {
    voltage_limit = voltage;

    setPower(this->power); // Update the output power when the limit changes
  }
}

// ===============================================================
// setPIN - Takes pins and sets class pins
// ===============================================================
void MotorController::setPIN(byte PIN_EN_1, byte PIN_EN_2, byte PIN_PWM) {
  this->PIN_EN_1 = PIN_EN_1;
  this->PIN_EN_2 = PIN_EN_2;
  this->PIN_PWM  = PIN_PWM;
}

#endif