/*
  Header for the temp sensor
*/

#ifndef TEMP_H
#define TEMP_H

// ==================================================================
// Includes
//  - TimeLoop:       Allows for scheduling periodic polling of
//                    the temp module
// ==================================================================
#include <Arduino.h>
#include "../TimedLoop/TimedLoop.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// ==================
// Parameter defines
// ==================
#define TEMP_BAUD_RATE        115200
#define TEMP_LOOP_DELAY       2000

#define TEMP_PIN_OUT          6

#define TEMP_SPOOF_DATA

class TEMP : public TimedLoop {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:
    byte PIN_ONE_WIRE;
    
    bool en;
    
    float temp;
    float temp_out;

    // =======================================================
    // loop() - Override the loop function from the TimedLoop 
    //          class
    // =======================================================
    void loop() override;


  public:
    // ======================================
    // Constructor: Take analog pin out
    // ======================================
    TEMP();
    TEMP(byte PIN);

    // =======================================================
    // setup() - Handles hardware setup after object creation
    // =======================================================
    void setup();

    // ===============================
    // Accessor methods
    // ===============================
    float getTemp();
    float getTempOut();
    void setPIN(byte PIN);
    void disableSensor();
};

#endif
