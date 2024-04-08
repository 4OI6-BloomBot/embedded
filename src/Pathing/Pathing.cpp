/*
  The AJ-SR04M wrapper class.
*/

#ifndef PATHING_CPP
#define PATHING_CPP

#define NO_LOGS

// Includes
#include "Pathing.h"

// ====================================================
// PATHING - Constructor for the  AJ-SR04M wrapper class
// ====================================================
PATHING::PATHING() : TimedLoop(PATHING_LOOP_DELAY) {
  // After assigning the pins run setup
  this->_SS.setPIN(A7, A4);      // echo, trig
  this->_MCL.setPIN(A5, A6, 9);  // pin 9 for pwm
  this->_MCR.setPIN(A2, A3, 5);  // pin 5 for pwm
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
    #ifndef NO_LOGS
      Serial.print(sat_cnt);
      Serial.println(" is current saturation count.");
    #endif

    if(en==0){
      stop();
    } else if(sat_cnt<SATURATION_LIMIT){
      forward();
      #ifndef NO_LOGS
        Serial.println("Moving forward");
      #endif
    } else if (sat_cnt>=SATURATION_LIMIT) {
      stop();
      delay(1000);
      r=random(2);

      if(r==0){
        #ifndef NO_LOGS
          Serial.println("Turning right 90 degrees");
        #endif
        turn_right();
      } else {
        #ifndef NO_LOGS
          Serial.println("Turning left 90 degrees");
        #endif
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
  this->_MCR.setPower(0.0);
  this->_MCL.setPower(0.0);
  this->_MCR.setDirection(STOPPED);
  this->_MCL.setDirection(STOPPED);
}

void PATHING::forward() {
  this->_MCR.setPower(0.25);
  this->_MCL.setPower(0.25);
  this->_MCR.setDirection(FORWARD);
  this->_MCL.setDirection(FORWARD);
}

void PATHING::turn_left() {
  this->_MCR.setPower(0.25);
  this->_MCL.setPower(0.25);
  this->_MCR.setDirection(FORWARD);
  this->_MCL.setDirection(BACKWARD);
  delay(TURN_TIME);
  stop();
}

void PATHING::turn_right() {
  this->_MCR.setPower(0.25);
  this->_MCL.setPower(0.25);
  this->_MCR.setDirection(BACKWARD);
  this->_MCL.setDirection(FORWARD);
  delay(TURN_TIME);
  stop();
}

#endif