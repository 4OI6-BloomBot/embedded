/*
  Parent class that implements a check to ensure that
  a task only occurs after X amount of time instead of 
  every iteration of the main program loop.

  Todo: Extend to enable low power status if nothing is
        scheduled anytime soon

  Todo: Need to account for the case where millis() overflows
        (~49 days)


  TODO: Should change the structure of this to queue events 
        to be run at a certain time.
        That way the system can be put into a low-power state
        for the periods where there are no events. 
        Would also need to implement interrupts for this
        (packet RX)
        Need to also ensure that high priority tasks (pump/movement)
        are always prioritized.
*/

#ifndef TIMED_LOOP_CPP
#define TIMED_LOOP_CPP

// Includes
#include "TimedLoop.h"


// ====================================================
// TimedLoop - Constructor.
// ====================================================
TimedLoop::TimedLoop(unsigned long int delay) {

  // Assign class variables 
  this->loop_delay    = delay;
  this->last_run_time = 0;

  setNextRuntime();
}


// ========================================================
// updateNextRuntime() - Set the next runtime
// ========================================================
void TimedLoop::setNextRuntime() {
  this->next_run_time = millis() + loop_delay;
}


// ========================================================
// tryLoop() - Check the current time against the set run
//             conditions. 
//             Call loop (abstract) if so.
// ========================================================
void TimedLoop::tryLoop() {
  unsigned long int current_time = millis();

  if (current_time >= next_run_time) {
    this->loop();
    last_run_time = current_time;
    setNextRuntime();
  }
}


// ========================================================
// getLastRuntime() - Accessor method for last runtime
// ========================================================
unsigned long int TimedLoop::getLastRuntime() {
  return this->last_run_time;
}

#endif