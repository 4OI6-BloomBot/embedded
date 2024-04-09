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
  this->_MC.setPIN(0, 0, 10);

  // Initialize packet_handler to null pointer
  // Will be updated by the packet handler once it is initialized
  this->packet_handler = nullptr;
}

// =======================================
// setup() - Initial setup
// =======================================
void Dispersion::setup(PacketHandler *p) {
  this->packet_handler = p;
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

long int Dispersion::dispersionAlgo(bool is_detected) {
  if (is_detected) {
      this->shutoff_time = DISP_TIME*1000 + millis();
      enablePump();
      sendDisp();
  } else {
    if (millis() >= this->shutoff_time) {
      disablePump();
    }

  }
  return this->shutoff_time;
}

// ====================================
// Send dispersion data to the server 
// ====================================
void Dispersion::sendDisp() {
  // Create a new packet and add data
  Deposit *packet = new Deposit();
  packet->addVal(DISP_TIME);

  this->packet_handler->queuePacket(packet);
}

#endif
