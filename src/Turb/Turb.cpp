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
TURB::TURB() : TimedLoop(TURB_LOOP_DELAY) {
}

TURB::TURB(byte PIN_OUT) : TimedLoop(TURB_LOOP_DELAY) {
  // Assign class variables 
  setPIN(PIN_OUT);

  // After assigning the pins run setup
  setup();
}

// =======================================
// setup() - Initial setup
// =======================================
void TURB::setup() {
  turb      = -1;
  this->en  = 1;

  TimedLoop::setup();
}

// =========================================================================
// loop() - Keeps turb variable up to date
// =========================================================================
void TURB::loop() {
  if(this->en == 1) {
    turb_out = getTurb();
  }
  else {
    turb_out = -1;
  }
}


// =======================================================
// getTurb() - Returns voltage for turb (lower is darker)
// =======================================================
float TURB::getTurb() {
  analogReference(EXTERNAL); // 5V
  int sensorValue = analogRead(this->PIN_OUT);// read the input on analog pin A0:
  float turbVolt = sensorValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):

  this->turb = turbVolt;


  return this->turb;
}

void TURB::setPIN(byte PIN_OUT) {
  this->PIN_OUT = PIN_OUT;
}

float TURB::getTurbOut() {
  return this->turb_out;
}

void TURB::disableSensor() {
  this->en = 0;
}

#endif