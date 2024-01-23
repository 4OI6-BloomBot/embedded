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


  // After assigning the pins run setup
  setup();
}

// =======================================
// setup() - Initial setup
// =======================================
void Dispersion::setup() {
  

}

// =========================================================================
// loop() - Keeps sensor variables up to date
// =========================================================================
void Dispersion::loop() {

}


#endif
