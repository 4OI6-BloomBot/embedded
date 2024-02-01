/*
  The Dispersion wrapper class.
*/

#ifndef DISPERSION_CPP
#define DISPERSION_CPP

// #define TEST

// Includes
#include "Dispersion.h"

// ====================================================
// DISPERSION - Constructor for the Dispersion wrapper class
// ====================================================
Dispersion::Dispersion() : TimedLoop(DISPERSION_LOOP_DELAY) {
  // Call sensor constructors
  // PINS are D8, D9, D10
  // TODO: figure out correct pins
  this->_MC.setPIN(8, 9, 10); // <--- guessing

  // After assigning the pins run setup
  setup();
}

// =======================================
// setup() - Initial setup
// =======================================
void Dispersion::setup() {
  this->_MC.setDirection(FORWARD);
}

// =========================================================================
// loop() 
// =========================================================================
void Dispersion::loop() {
}

void Dispersion::enablePump() {
  this->_MC.setPower(1.0);
}
void Dispersion::disablePump() {
  this->_MC.setPower(0.0);
}

#endif
