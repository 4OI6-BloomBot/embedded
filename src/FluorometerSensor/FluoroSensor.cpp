/*
  The Fluoro wrapper class.
*/

#ifndef FLUORO_CPP
#define FLUORO_CPP

// Includes
#include "FluoroSensor.h"

// ====================================================
// FLUORO - Constructor for the fluoro wrapper class
// ====================================================
// FLUORO::FLUORO(byte PIN_OUT) : TimedLoop(FLUORO_LOOP_DELAY) {
FLUORO::FLUORO() : TimedLoop(FLUORO_LOOP_DELAY) {
}

FLUORO::FLUORO(byte PIN_OUT) : TimedLoop(FLUORO_LOOP_DELAY) {

  // Assign class variables 
  setPIN(PIN_OUT);
}

// =======================================
// setup() - Initial setup
// =======================================
void FLUORO::setup() {
  this->fluoro  = -1;
  this->en      = 1;

  TimedLoop::setup();

  pinMode(LED_PIN, OUTPUT);
}

// =========================================================================
// loop() - Keeps fluoro variable up to date
// =========================================================================
void FLUORO::loop() {
  if (this->en == 1) {
    this->fluoro_out = getFluoro();
  } 
  else {
    this->fluoro_out = -1;
  }
}


// =======================================================
// getFluoro() - Returns voltage for fluoro (lower is darker)
// =======================================================
float FLUORO::getFluoro() {
  analogReference(EXTERNAL); // EXTERNAL == 5V
  int ana_value = analogRead(this->PIN_OUT);  // read the input on analog pin A1:
  this->fluoro = ana_value; 
  return ana_value;
}

void FLUORO::setPIN(byte PIN_OUT) {
  this->PIN_OUT = PIN_OUT;
}

float FLUORO::getFluoroOut() {
  return this->fluoro_out;
}

void FLUORO::enableLED() {
  digitalWrite(LED_PIN, HIGH);
}

void FLUORO::disableLED() {
  digitalWrite(LED_PIN, LOW);
}

void FLUORO::disableSensor() {
  disableLED();
  this->en = 0;
}

#endif