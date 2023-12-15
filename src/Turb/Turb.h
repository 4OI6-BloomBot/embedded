/*
  Header for the turb sensor
*/

#ifndef TURB_H
#define TURB_H

// ==================================================================
// Includes
//  - TimeLoop:       Allows for scheduling periodic polling of
//                    the turb module
//  - SoftwareSerial: Required to interface with the turb sensor
// ==================================================================
#include <Arduino.h>
#include "../TimedLoop/TimedLoop.h"
#include <SoftwareSerial.h>

// ==================
// Parameter defines
// ==================
#define TURB_BAUD_RATE       9600
#define TURB_LOOP_DELAY      2000 // How often are we probing turb? (2 seconds)


class TURB : public TimedLoop {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:
    byte PIN_OUT;

    float turb;
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
    // Constructor: Takes TX & RX pin inputs
    // ======================================
    TURB(byte PIN_OUT);

    // ===============================
    // getDistance: Accessor method
    // ===============================
    float getTurb();
};

#endif