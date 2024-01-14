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


// ==================
// Parameter defines
// ==================
#define DETECTION_BAUD_RATE         115200
#define DETECTION_LOOP_DELAY        5000
#define DELTA_TURB_THRESHOLD        1
#define TEMP_THRESHOLD              25
#define DELTA_TEMP_THRESHOLD        5
#define IS_DETECTED_THRESHOLD       3


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

    int detect_count;
    bool is_detected;

    // TURB turb(byte);


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
    Detection();



    // ===============================
    // monitorDetection: monitor method
    // ===============================
    bool monitorDetection();
};

#endif