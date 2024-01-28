/*
  Header for the Dispersion class
*/

#ifndef DISPERSION_H
#define DISPERSION_H

// ==================================================================
// Includes
//  - TimeLoop:       Allows for scheduling periodic polling of
//                    the detection module
// ==================================================================
#include <Arduino.h>
#include "../MotorController/MotorController.h"

// ==================
// Parameter defines
// ==================
#define DISPERSION_BAUD_RATE         115200
#define DISPERSION_LOOP_DELAY        3000


class Dispersion : public TimedLoop {

  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:

    MotorController _MC;

    // =======================================================
    // loop() - Override the loop function from the TimedLoop 
    //          class
    // =======================================================
    void loop() override;

    // =======================================================
    // setup() - Handles hardware setup after object creation
    // =======================================================
    void setup();



  public:
    // ======================================
    // Constructor: Take analog pin out
    // ======================================
    Dispersion();

    void enablePump();
    void disablePump();

 

};

#endif
