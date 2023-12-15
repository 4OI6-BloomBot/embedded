/*
  The Turb wrapper class.
*/

#ifndef TURB_CPP
#define TURB_CPP

// Includes
#include "Turb.h"

// ====================================================
// TURB - Constructor for the turb wrapper class
// ====================================================
TURB::TURB(byte PIN_OUT) : TimedLoop(TURB_LOOP_DELAY) {

  // Assign class variables 
  this->PIN_OUT = PIN_OUT;

  // After assigning the pins run setup
  setup();
}

// =======================================
// setup() - Initial setup
// =======================================
void TURB::setup() {
  turb=-1;
}

// =========================================================================
// loop() - Keeps turb variable up to date
// =========================================================================
void TURB::loop() {
    getTurb();
}


// =======================================================
// getTurb() - Returns voltage for turb (lower is darker)
// =======================================================
float TURB::getTurb() {
  int sensorValue = analogRead(PIN_OUT);// read the input on analog pin A0:
  turb = sensorValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):

  Serial.print(turb);
  Serial.println(" V");

  return turb;
}

#endif