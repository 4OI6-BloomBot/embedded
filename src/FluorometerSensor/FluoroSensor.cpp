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
  // After assigning the pins run setup
  setup();
}

FLUORO::FLUORO(byte PIN_OUT) : TimedLoop(FLUORO_LOOP_DELAY) {

  // Assign class variables 
  setPIN(PIN_OUT);
  

  // After assigning the pins run setup
  setup();
}

// =======================================
// setup() - Initial setup
// =======================================
void FLUORO::setup() {
  this->fluoro=-1;
  pinMode(LED_PIN, OUTPUT);
}

// =========================================================================
// loop() - Keeps fluoro variable up to date
// =========================================================================
void FLUORO::loop() {
  this->fluoro_out = getFluoro();
}


// =======================================================
// getFluoro() - Returns voltage for fluoro (lower is darker)
// =======================================================
float FLUORO::getFluoro() {
  float ana_value = analogRead(this->PIN_OUT);  // read the input on analog pin A1:
  this->fluoro = ana_value * (5.0 / 1024.0);    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):

  return this->fluoro;
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

#endif