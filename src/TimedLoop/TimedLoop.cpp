/*
  Parent class that implements a check to ensure that
  a task only occurs after X amount of time instead of 
  every iteration of the main program loop.

  Todo: Extend to enable low power status if nothing is
        scheduled anytime soon

  Todo: Need to account for the case where millis() overflows
        (~49 days)
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

}


// ============================================
// tryLoop() - Check the current time against
//             the set run conditions. 
//             Call loop (abstract) if so.
// ============================================
void TimedLoop::tryLoop() {
  unsigned long int current_time = millis();

  if (current_time - last_run_time >= loop_delay) {
    this->loop();
    last_run_time = current_time;
  }
}


#endif