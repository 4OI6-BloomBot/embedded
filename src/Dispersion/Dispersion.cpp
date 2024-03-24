/*
  The Dispersion wrapper class.
*/

#ifndef DISPERSION_CPP
#define DISPERSION_CPP

#define NO_LOGS

// Includes
#include "Dispersion.h"

// ====================================================
// DISPERSION - Constructor for the Dispersion wrapper class
// ====================================================
Dispersion::Dispersion() : TimedLoop(DISPERSION_LOOP_DELAY) {
  // Call sensor constructors
  this->_MC.setPIN(8, 9, 10);
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

void Dispersion::dispersionAlgo(bool is_detected) {
  if (is_detected) {
      // Number of instances pump is activated for slow dispersion
      for (int i = 0; i < NUM_DISP; i++) {
        enablePump();
        // Length of time pump is enable at once (in factors of 10sec)
        for (int j = 0; j < DISP_TIME; j++) {
          delay(10000); // 10 sec
          #ifndef NO_LOGS
            Serial.print("PUMP: ");
            Serial.print((j+1)*10);
            Serial.println(" s");
          #endif
        }
        disablePump();
      }
    }
}

#endif
