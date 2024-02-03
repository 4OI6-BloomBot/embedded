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

// ====================
// Constant definition 
// ====================
#define CONTROLLER_INPUT_VOLTAGE 5


class MotorController {
  
  // ==================================================================
  // Private fields. 
  // - PIN_EN_1/2:        References to pins used to enable motor 1/2
  // - PIN_PWM:           Reference to PWM pin used to control motor
  //                      speed.
  // - current_direction: The current direction of the motor
  // - voltage_limit:     The maximum allowed output voltage
  // - power:             The power level output from the controller
  // ==================================================================
  private:
    byte PIN_EN_1;
    byte PIN_EN_2;
    byte PIN_PWM;

    direction current_direction;

    byte  voltage_limit;
    float power;


    // =======================================================
    // setup() - Handles hardware setup after object creation
    // =======================================================
    void setup();

  public:
    // =================================================
    // Constructor: Takes enable and PWM pins as inputs
    // =================================================
    MotorController(byte PIN_EN_1, byte PIN_EN_2, byte PIN_PWM);
    MotorController();


    // ========================================================
    // setDirection: Takes direction enum and sets enable pins
    // ========================================================
    void setDirection(direction dir);


    // ========================================================
    // setPower: Sets the speed of the motor by controlling
    //           the PWM output as a percentage.
    // ========================================================
    void setPower(float power);


    // ========================================================
    // setVoltageLimit: Configures the max output voltage from
    //                  the controller.
    // ========================================================
    void setVoltageLimit(byte voltage);

    // ========================================================
    // setPin: Configures enable and PWM pins
    // ========================================================
    void setPIN(byte PIN_EN_1, byte PIN_EN_2, byte PIN_PWM);

};

#endif