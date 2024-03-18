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
// TURB::TURB(byte PIN_OUT) : TimedLoop(TURB_LOOP_DELAY) {
TURB::TURB() : TimedLoop(TURB_LOOP_DELAY) {

  // Assign class variables 
  // this->PIN_OUT = PIN_OUT;
  // setPIN(PIN_OUT);

  // After assigning the pins run setup
  setup();
}

TURB::TURB(byte PIN_OUT) : TimedLoop(TURB_LOOP_DELAY) {

  // Assign class variables 
  // this->PIN_OUT = PIN_OUT;
  setPIN(PIN_OUT);

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
    turb_out = getTurb();
}


// =======================================================
// getTurb() - Returns voltage for turb (lower is darker)
// =======================================================
float TURB::getTurb() {
  analogReference(EXTERNAL); // 5V
  int sensorValue = analogRead(this->PIN_OUT);// read the input on analog pin A0:
  this->turb = sensorValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):

  this->turb = -1120.4*pow(this->turb, 2) + 5742.3*this->turb - 4352.9;

  return this->turb;
}

void TURB::setPIN(byte PIN_OUT) {
  this->PIN_OUT = PIN_OUT;
}

float TURB::getTurbOut() {
  return this->turb_out;
}

#endif