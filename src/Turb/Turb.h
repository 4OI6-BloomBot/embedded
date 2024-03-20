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
#define TURB_BAUD_RATE        115200
#define TURB_LOOP_DELAY       2000 // How often are we probing turb? (2 seconds)

#define TURB_PIN_OUT          A0

class TURB : public TimedLoop {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:
    byte PIN_OUT;
  
    bool en;

    float turb;
    float turb_out;
    // =======================================================
    // loop() - Override the loop function from the TimedLoop 
    //          class
    // =======================================================
    void loop() override;


  public:
    // ======================================
    // Constructor: Take analog pin out
    // ======================================
    // TURB(byte PIN_OUT);
    TURB();
    TURB(byte PIN_OUT);

    // =======================================================
    // setup() - Handles hardware setup after object creation
    // =======================================================
    void setup();

    // ===============================
    // getDistance: Accessor method
    // ===============================
    float getTurb();
    float getTurbOut();
    void setPIN(byte PIN_OUT);
    void disableSensor();
};

#endif