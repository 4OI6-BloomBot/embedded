/*
  Header for the Detection class
*/

#ifndef DETECTION_H
#define DETECTION_H

// ==================================================================
// Includes
//  - TimeLoop:       Allows for scheduling periodic polling of
//                    the detection module
// ==================================================================
#include <Arduino.h>
#include "../TimedLoop/TimedLoop.h"
#include "../Turb/Turb.h"
#include "../TemperatureSensor/TempSensor.h"
#include "../FluorometerSensor/FluoroSensor.h"
#include "../Dispersion/Dispersion.h"

#define THRESHOLD_TEST

// ==================
// Parameter defines
// ==================
#define DETECTION_BAUD_RATE         115200
#define DETECTION_LOOP_DELAY        1000
#define IS_DETECTED_THRESHOLD       4

#ifndef THRESHOLD_TEST
  #define DELTA_TURB_THRESHOLD        1
  #define TEMP_THRESHOLD              25
  #define DELTA_TEMP_THRESHOLD        5
  #define FLUORO_THRESHOLD            3
#else
  #define DELTA_TURB_THRESHOLD        0
  #define TEMP_THRESHOLD              25
  #define DELTA_TEMP_THRESHOLD        0.5
  #define FLUORO_THRESHOLD            3
#endif

class Detection : public TimedLoop {

  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:
    float curr_turb;
    float prev_turb;
    float delta_turb;
    float curr_temp;
    float prev_temp;
    float delta_temp;
    float curr_fluoro;
    float prev_fluoro;
    float delta_fluoro;
    int detect_count;
    bool is_detected;

    float fluoro_arr[10];
    int fluoro_count;

    TURB _turb;
    TEMP _temp;
    FLUORO _fluoro;
    Dispersion _disp;

    // =======================================================
    // loop() - Override the loop function from the TimedLoop 
    //          class
    // =======================================================
    void loop() override;

    // =======================================================
    // setup() - Handles hardware setup after object creation
    // =======================================================
    void setup();

    void displayData();


  public:
    // ======================================
    // Constructor: Take analog pin out
    // ======================================
    Detection();

    // ===============================
    // monitorDetection: monitor method
    // ===============================
    bool monitorDetection();

};

#endif
