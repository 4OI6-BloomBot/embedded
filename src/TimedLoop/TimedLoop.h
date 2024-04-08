/*
  Header for timer parent class
*/

#ifndef TIMED_LOOP_H
#define TIMED_LOOP_H

// ==================================================================
// Includes
// ==================================================================
#include <Arduino.h>


// ==================================================================
// Params
// ==================================================================
#define NUM_TIMEDLOOP_OBJECTS 15


class TimedLoop {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:

    // =============================================================
    // Static list of TimedLoop objects that is filled at startup
    // Used to determine/handle next event times.
    // Counting int keeps track of how many objects are assigned
    // =============================================================
    static TimedLoop* timedObjects[NUM_TIMEDLOOP_OBJECTS];
    static int        objectCount;


    // ============================================================= 
    // Configuration and run time tracking
    // =============================================================
    unsigned long int last_run_time;
    unsigned long int next_run_time;
    unsigned long int loop_delay;

   
    // =============================================================
    // Loop to run in the main loop when the timing is appropriate.
    // Abstract, needs to be implemented by the child class 
    // =============================================================
    virtual void loop() = 0;


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


    void setup();


    // ====================================================
    // tryEvents() - Goes through the static list of 
    //               objects and runs tryLoop on each
    // ====================================================
    static void tryEvents();


    // ====================================================
    // Setter/accessor methods
    // ====================================================
           unsigned long int  getLastRuntime();
    static void               addObject(TimedLoop *obj);
    static unsigned long int  getTimeToNextEvent();

};

#endif