/*
  The AJ-SR04M wrapper class.
*/

#ifndef PATHING_CPP
#define PATHING_CPP

// Includes
#include "Pathing.h"

// ====================================================
// PATHING - Constructor for the  AJ-SR04M wrapper class
// ====================================================
PATHING::PATHING() : TimedLoop(PATHING_LOOP_DELAY) {
  // After assigning the pins run setup
  this->_SS.setPIN(11,12);
  this->_MCL.setPIN(7,8,9);
  this->_MCR.setPIN(3,4,5);
  setup();
}

// =======================================
// setup() - Configure the pin directions
// =======================================
void PATHING::setup() {
  _SS.setup();
  TimedLoop::setup();
  
  // Create new objects and add to pointers
  en=1;
  sat_cnt=0;
  dist=-1;
  this->_MCR.setDirection(STOPPED);
  this->_MCL.setDirection(STOPPED);
}

// =========================================================================
// loop() - Keeps distance variable up to date
// =========================================================================
void PATHING::loop() {

    dist=_SS.peekDistance();

    if(dist<TOO_CLOSE && sat_cnt<SATURATION_LIMIT){
      sat_cnt=sat_cnt+1;
    } else if (dist>=TOO_CLOSE && sat_cnt>=1) {
      sat_cnt=sat_cnt-1;
    }

    Serial.print(sat_cnt);
    Serial.println(" is current saturation count.");

    if(en==0){
      stop();
    } else if(sat_cnt<SATURATION_LIMIT){
      forward();
      Serial.println("Moving forward");
    } else if (sat_cnt>=SATURATION_LIMIT) {
      stop();
      delay(1000);
      r=random(2);

      if(r==0){
        Serial.println("Turning right 90 degrees");
        turn_right();
      } else {
        Serial.println("Turning left 90 degrees");
        turn_left();
      }

    }
}


void PATHING::enable() {
if(en==0){
Serial.println("Pathing restarting");
}
en=1;
}

void PATHING::disable() {
Serial.println("Pathing disabled");
en=0;
}

void PATHING::stop() {
  this->_MCR.setDirection(STOPPED);
  this->_MCL.setDirection(STOPPED);
}

void PATHING::forward() {
  this->_MCR.setDirection(FORWARD);
  this->_MCL.setDirection(FORWARD);
}

void PATHING::turn_left() {
  this->_MCR.setDirection(FORWARD);
  this->_MCL.setDirection(BACKWARD);
  delay(TURN_TIME);
  stop();
}

void PATHING::turn_right() {
  this->_MCR.setDirection(BACKWARD);
  this->_MCL.setDirection(FORWARD);
  delay(TURN_TIME);
  stop();
}

#endif