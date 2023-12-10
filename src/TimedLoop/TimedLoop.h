/*
  Header for timer parent class
*/

#ifndef TIMED_LOOP_H
#define TIMED_LOOP_H

// ==================================================================
// Includes
//  - TinyGPS++:      Helps to parse NMEA data that is output from 
//                    the GPS module
//  - SoftwareSerial: Required to interface with the GPS module
// ==================================================================
#include <Arduino.h>



// ==================
// Parameter defines
// ==================
#define LOOP_RUN_RATE

class TimedLoop {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:

    unsigned long int last_run_time;
    unsigned long int loop_delay;
   
    // =============================================================
    // Loop to run in the main loop when the timing is appropriate.
    // Abstract, needs to be implemented by the child class 
    // =============================================================
    virtual void loop();


  public:
    // =========================================================
    // Constructor: Takes the delay period in ticks as an input
    // =========================================================
    TimedLoop(unsigned long int delay);

    // ====================================================
    // Checks the current time against the run conditions.
    // Calls the loop function if the delay period has 
    // passed
    // ====================================================
    void tryLoop();

};

#endif