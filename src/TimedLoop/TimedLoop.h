/*
  Header for timer parent class
*/

#ifndef TIMED_LOOP_H
#define TIMED_LOOP_H

// ==================================================================
// Includes
// ==================================================================
#include <Arduino.h>


class TimedLoop {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:

    // Configuration and run time tracking
    unsigned long int last_run_time;
    unsigned long int next_run_time;
    unsigned long int loop_delay;
   
    // =============================================================
    // Loop to run in the main loop when the timing is appropriate.
    // Abstract, needs to be implemented by the child class 
    // =============================================================
    virtual void loop();

    // =============================================================
    // Update the next runtime parameter to be one delay period
    // from the current time.
    // =============================================================
    void setNextRuntime();


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


    // ====================================================
    // Setter/accessor methods
    // ====================================================
    unsigned long int getLastRuntime();

};

#endif