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
// setup() - Configure the pin directions
// =======================================
void TURB::setup() {
  // Create new objects and add to pointers
  turb=-1;
}

// =========================================================================
// loop() - Waits for data from the GPS module and updates the parser.
// =========================================================================
void TURB::loop() {
    getTurb();
}


// =======================================================
// getLocation() - Returns a struct with updated lat/long
//                 coordinates from the GPS module
//                 If the data is too old or not available
//                 a null pointer is returned.
// =======================================================
float TURB::getTurb() {
  int sensorValue = analogRead(PIN_OUT);// read the input on analog pin A0:
  turb = sensorValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):

  Serial.print(turb);
  Serial.println(" V");

  return turb;
}

#endif