/*
  Header for the AJ-SR04M wrapper header class.
*/

#ifndef PATHING_H
#define PATHING_H

// ==================================================================
// Includes
//  - TimeLoop:       Allows for scheduling periodic polling of
//                    the PATHING module
//  - SoftwareSerial: Required to interface with the PATHING sensor
// ==================================================================
#include <Arduino.h>
#include "../TimedLoop/TimedLoop.h"
#include <SoftwareSerial.h>
#include "../SonicSensor/SonicSensor.h"
#include "../MotorController/MotorController.h"

// ==================
// Parameter defines
// ==================
#define PATHING_BAUD_RATE       115200
#define PATHING_LOOP_DELAY      2000 // How often are we probing distance? (2 seconds)
#define SATURATION_LIMIT        3
#define TOO_CLOSE               35
#define TURN_TIME               2000


class PATHING : public TimedLoop {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:
    int en;
    int dist;
    int sat_cnt;
    long r;
    SONIC _SS;
    MotorController _MCL;
    MotorController _MCR;
    // =======================================================
    // loop() - Override the loop function from the TimedLoop 
    //          class
    // =======================================================
    void loop() override;


  public:
    // ======================================
    // Constructor: Takes Echo and trig pins for module
    // ======================================
    PATHING();


    // =======================================================
    // setup() - Handles hardware setup after object creation
    // =======================================================
    void setup();


    // ===============================
    // getDistance: Accessor method
    // ===============================
    void enable();
    void disable();
    void turn_right();
    void turn_left();
    void forward();
    void stop();
};

#endif