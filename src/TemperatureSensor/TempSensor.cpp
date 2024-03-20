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
}

TEMP::TEMP(byte PIN) : TimedLoop(TEMP_LOOP_DELAY) {
  // Assign class variables 
  setPIN(PIN);
}

// =======================================
// setup() - Initial setup
// =======================================
void TEMP::setup() {
  temp      = -1;
  this->en  = 1;

  TimedLoop::setup();
}

// =========================================================================
// loop() - Keeps turb variable up to date
// =========================================================================
void TEMP::loop() {
  if (this->en == 1) {
    this->temp_out = getTemp();
  }
  else {
    this->temp_out = -1;
  }
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

void TEMP::disableSensor() {
  this->en = 0;
}

#endif