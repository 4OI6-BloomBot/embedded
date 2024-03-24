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

// ==================
// Parameter defines
// ==================
#define DETECTION_BAUD_RATE         115200
#define DETECTION_LOOP_DELAY        3000

// ====================================
// Thresholds for detection algo
// ====================================
#define IS_DETECTED_THRESHOLD       5

#define TURB_THRESHOLD              3.5     // 3.5V ~= 5-100, anything bellow can be considered 
#define DELTA_TURB_THRESHOLD        0.3     // Change of 0.3 V ~= +- 100-1000 NTU 
#define TEMP_THRESHOLD              25      // Blooms happen > 25 deg C
#define DELTA_TEMP_THRESHOLD        0       // Temperature theoretically should increase, hard to detect in nature
#define FLUORO_THRESHOLD            0       // TODO: unknown RN

#define TIMEOUT                     30      // Seconds


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

    bool en_pump;
    bool en_sensor;

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

    void displayData();


  public:
    // Thresholds can be modified through configuration packets
    // TODO: Could also make these private w/ getter+setter methods
    float turb_threshold       = TURB_THRESHOLD;
    float delta_turb_threshold = DELTA_TURB_THRESHOLD;
    float temp_threshold       = TEMP_THRESHOLD;
    float delta_temp_threshold = DELTA_TEMP_THRESHOLD;
    float fluoro_threshold     = TURB_THRESHOLD;

    // ======================================
    // Constructor: Take analog pin out
    // ======================================
    Detection();

    // =======================================================
    // setup() - Handles hardware setup after object creation
    // =======================================================
    void setup();

    // ===============================
    // monitorDetection: monitor method
    // ===============================
    bool monitorDetection();

    void disablePump();
    void disableAllSensors();
    void resetSensorData();

    // Accessor methods for the sensors
    TURB*   getTurb();
    TEMP*   getTemp();
    FLUORO* getFluoro();

    bool bloomDetect();

};

#endif
