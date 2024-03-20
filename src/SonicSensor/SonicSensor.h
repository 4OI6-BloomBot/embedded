/*
  Header for the AJ-SR04M wrapper header class.
*/

#ifndef SONIC_H
#define SONIC_H

// ==================================================================
// Includes
//  - TimeLoop:       Allows for scheduling periodic polling of
//                    the sonic module
//  - SoftwareSerial: Required to interface with the sonic sensor
// ==================================================================
#include <Arduino.h>
#include "../TimedLoop/TimedLoop.h"
#include <SoftwareSerial.h>

// ==================
// Parameter defines
// ==================
#define SONIC_BAUD_RATE       115200
#define SONIC_LOOP_DELAY      2000 // How often are we probing distance? (2 seconds)


class SONIC : public TimedLoop {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:
    byte PIN_ECHO;
    byte PIN_TRIG;
    int distance;

    // =======================================================
    // loop() - Override the loop function from the TimedLoop 
    //          class
    // =======================================================
    void loop() override;


  public:
    // ======================================
    // Constructor: Takes Echo and trig pins for module
    // ======================================
    SONIC();

    // =======================================================
    // setup() - Handles hardware setup after object creation
    // =======================================================
    void setup();

    // ===============================
    // getDistance: Polls distance
    // ===============================
    int getDistance();

    
    int peekDistance();
    void setPIN(byte PIN_ECHO,byte PIN_TRIG);
};

#endif