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
  TimedLoop::setup();

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
  analogReference(INTERNAL); // INTERNAL == 0.55V
  int ana_value = analogRead(this->PIN_OUT);  // read the input on analog pin A1:
  // Serial.print("src: ");
  // Serial.println(ana_value);
  this->fluoro = ana_value; //* (1.1 / 1024.0);    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):

  // return this->fluoro;
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

#endif