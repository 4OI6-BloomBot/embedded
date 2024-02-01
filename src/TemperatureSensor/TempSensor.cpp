/*
  The Temp wrapper class.
*/

#ifndef TEMP_CPP
#define TEMP_CPP

// Includes
#include "TempSensor.h"

// ====================================================
// TEMP - Constructor for the turb wrapper class
// ====================================================
TEMP::TEMP() : TimedLoop(TEMP_LOOP_DELAY) {
  // After assigning the pins run setup
  setup();
}

TEMP::TEMP(byte PIN) : TimedLoop(TEMP_LOOP_DELAY) {
  // Assign class variables 
  setPIN(PIN);
  // After assigning the pins run setup
  setup();
}

// =======================================
// setup() - Initial setup
// =======================================
void TEMP::setup() {
  temp = -1;
}

// =========================================================================
// loop() - Keeps turb variable up to date
// =========================================================================
void TEMP::loop() {
    this->temp_out = getTemp();
}


// =======================================================
// getTemp() - 
// =======================================================
float TEMP::getTemp() {
  OneWire oneWire(this->PIN_ONE_WIRE);
  DallasTemperature tempSensor(&oneWire);

  tempSensor.begin();
  tempSensor.requestTemperatures();
  this->temp = tempSensor.getTempCByIndex(0);

  return this->temp;
}

void TEMP::setPIN(byte PIN) {
  this->PIN_ONE_WIRE = PIN;
}

float TEMP::getTempOut() {
  return this->temp_out;
}

#endif