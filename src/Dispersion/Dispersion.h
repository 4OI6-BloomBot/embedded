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
#include "../TimedLoop/TimedLoop.h"
#include "../MotorController/MotorController.h"

// ==================
// Parameter defines
// ==================
#define DISPERSION_BAUD_RATE         115200
#define DISPERSION_LOOP_DELAY        3000

#define NUM_DISP                     1     // Number of iterations
#define DISP_TIME                    6      // DISP_TIME*10sec = total time


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


  public:
    // ======================================
    // Constructor: Take analog pin out
    // ======================================
    Dispersion();

    // =======================================================
    // setup() - Handles hardware setup after object creation
    // =======================================================
    void setup();

    void enablePump();
    void disablePump();

    void dispersionAlgo(bool is_detected);

 

};

#endif
