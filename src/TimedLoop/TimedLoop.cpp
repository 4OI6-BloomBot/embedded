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
// Static variable initialization
// ====================================================
TimedLoop* TimedLoop::timedObjects[NUM_TIMEDLOOP_OBJECTS] = {nullptr};


// ====================================================
// TimedLoop - Constructor.
// ====================================================
TimedLoop::TimedLoop(unsigned long int delay) {

  // Assign class variables 
  this->loop_delay    = delay;
  this->last_run_time = 0;

  setNextRuntime();

  // Add object to list
  TimedLoop::addObject(this);
}


// ========================================================
// updateNextRuntime() - Set the next runtime and update
//                       static next event time.
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
// tryEvents() - Calls tryLoop on each of the objects in
//               the static list
// ========================================================
void TimedLoop::tryEvents() {
  for (int i = 0; i < NUM_TIMEDLOOP_OBJECTS; i++)
    TimedLoop::timedObjects[i]->tryLoop();
}


// ========================================================
// getLastRuntime() - Accessor method for last runtime
// ========================================================
unsigned long int TimedLoop::getLastRuntime() {
  return this->last_run_time;
}


// ========================================================
// addObject() - Add an object to the static list of 
//               TimedLoop objects.
// ========================================================
void TimedLoop::addObject(TimedLoop *obj) {
  // ======================================================================
  // Iterate over all of the objects and add the given pointer to the next
  // free slot
  // ======================================================================
  for (int i = 0; i < NUM_TIMEDLOOP_OBJECTS; i++) {
    if (TimedLoop::timedObjects[i] == nullptr) {
      TimedLoop::timedObjects[i] = obj;
      return;
    }
  }
}

// ======================================================================
// getTimeToNextEvent() - Static method that returns the time (in millis)
//                        until the next event
// ======================================================================
unsigned long int TimedLoop::getTimeToNextEvent() {
  unsigned long int next_time = (unsigned long) - 1; // Set to max value
  unsigned long int obj_time;

  for (int i = 0; i < NUM_TIMEDLOOP_OBJECTS; i++) {
    obj_time = TimedLoop::timedObjects[i]->next_run_time;
    
    if (obj_time < next_time && obj_time > millis())
      next_time = obj_time;
  }

  // TODO: Might need to handle this differently
  if (next_time == (unsigned long) - 1) return 0;
  else                                  return next_time - millis();
}

#endif