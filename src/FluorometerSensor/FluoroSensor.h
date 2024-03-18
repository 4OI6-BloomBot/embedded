/*
  Header for the fluoro sensor
*/

#ifndef FLUORO_H
#define FLUORO_H

// ==================================================================
// Includes
//  - TimeLoop:       Allows for scheduling periodic polling of
//                    the fluoro module
// ==================================================================
#include <Arduino.h>
#include "../TimedLoop/TimedLoop.h"

// ==================
// Parameter defines
// ==================
#define FLUORO_BAUD_RATE        115200
#define FLUORO_LOOP_DELAY       1000 

#define LED_PIN                 12
#define FLUORO_PIN_OUT          A1


class FLUORO : public TimedLoop {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:
    byte PIN_OUT;

    float fluoro;
    float fluoro_out;
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
    FLUORO();
    FLUORO(byte PIN_OUT);

    // ===============================
    // Fluorometer Functions
    // ===============================
    float getFluoro();
    float getFluoroOut();
    void setPIN(byte PIN_OUT);

    // ===============================
    // LED Functions
    // ===============================
    void enableLED();
    void disableLED();
};

#endif