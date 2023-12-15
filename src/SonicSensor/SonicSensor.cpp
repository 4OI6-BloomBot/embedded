/*
  The AJ-SR04M wrapper class.
*/

#ifndef SONIC_CPP
#define SONIC_CPP

// Includes
#include "SonicSensor.h"

// ====================================================
// SONIC - Constructor for the  AJ-SR04M wrapper class
// ====================================================
SONIC::SONIC(byte PIN_ECHO, byte PIN_TRIG) : TimedLoop(SONIC_LOOP_DELAY) {

  // Assign class variables 
  this->PIN_ECHO = PIN_ECHO;
  this->PIN_TRIG = PIN_TRIG;

  // After assigning the pins run setup
  setup();
}

// =======================================
// setup() - Configure the pin directions
// =======================================
void SONIC::setup() {
  // Create new objects and add to pointers
  distance=-1;
}

// =========================================================================
// loop() - Keeps distance variable up to date
// =========================================================================
void SONIC::loop() {
    getDistance();
}


// =======================================================
// getDistnace() - Returns distance in cm. -1 is invalid. Sensor ets messy when <20cm
// =======================================================
int SONIC::getDistance() {

  long duration, distance_calc;
  digitalWrite(PIN_TRIG, LOW);  
  delayMicroseconds(2); 
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  duration = pulseIn(PIN_ECHO, HIGH);
  distance_calc = (duration/2) / 29.1;

  if (distance_calc >= 200 || distance_calc <= 0){
    distance=-1;
  }
  else {
    distance=(int)distance_calc;
  }

Serial.print(distance);
Serial.println(" cm");

return distance;
}

#endif