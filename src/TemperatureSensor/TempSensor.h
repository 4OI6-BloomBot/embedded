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
#define TEMP_BAUD_RATE       115200
#define TEMP_LOOP_DELAY      2000


class TEMP : public TimedLoop {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:
    byte PIN_ONE_WIRE;
    
    float temp;
    float temp_out;

    DallasTemperature tempSensor;


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
    TEMP();
    TEMP(byte PIN);

    // ===============================
    // Accessor methods
    // ===============================
    float getTemp();
    float getTempOut();
    void setPIN(byte PIN);
};

#endif
