/*
  Class for the L298N Motor Controllers
*/

#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

// =================
// Includes
// =================
#include <Arduino.h>;


// =================
// Enum definition
// =================
enum direction {FORWARD, BACKWARD, STOPPED};


class MotorController {
  
  // ==================================================================
  // Private fields. 
  // - PIN_EN_1/2:        References to pins used to enable motor 1/2
  // - PIN_PWM:           Reference to PWM pin used to control motor
  //                      speed.
  // - current_direction: The current direction of the motor
  // ==================================================================
  private:
    byte PIN_EN_1;
    byte PIN_EN_2;
    byte PIN_PWM;

    direction current_direction;


    // =======================================================
    // setup() - Handles hardware setup after object creation
    // =======================================================
    void setup();

  public:
    // =================================================
    // Constructor. Takes enable and PWM pins as inputs
    // =================================================
    MotorController(byte PIN_EN_1, byte PIN_EN_2, byte PIN_PWM);

    void setDirection(direction dir);

};

#endif