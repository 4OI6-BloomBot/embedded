/*
  Wrapper class for the NEO-6M GPS.
*/

#ifndef GPS_CPP
#define GPS_CPP

// Includes
#include "GPS.h"

// ====================================================
// GPS - Constructor for the NEO-6M GPS wrapper class.
// ====================================================
GPS::GPS(byte PIN_TX, byte PIN_RX) {

  // Assign class variables 
  this->PIN_TX = PIN_TX;
  this->PIN_RX = PIN_RX;

  // After assigning the pins run setup
  setup();
}


// =======================================
// setup() - Configure the pin directions
// =======================================
void GPS::setup() {
  
  // Set the pin types
  pinMode(PIN_TX, OUTPUT);
  pinMode(PIN_RX, INPUT);
 
}

#endif