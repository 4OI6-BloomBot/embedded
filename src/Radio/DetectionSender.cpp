/*
  Class to manage packaging and sending location data.
*/

#ifndef LOCATION_SENDER_CPP
#define LOCATION_SENDER_CPP

// Includes
#include "DetectionSender.h"
#include "../Radio/PacketHandler.h"

// =========================================================================
// Constructor
// =========================================================================
DetectionSender::DetectionSender(PacketHandler *packet_handler) : TimedLoop(DETECTION_SENDER_LOOP_DELAY) {
  this->packet_handler = packet_handler;

  // Set to defaults
  this->isConfigured       = false;
  this->turb_last_access   = (unsigned long int) - 1;
  this->temp_last_access   = (unsigned long int) - 1;
  this->fluoro_last_access = (unsigned long int) - 1;
}

// =========================================================================
// loop - TimedLoop override
//        TODO: Need to check if the location has updated before
//              sending.
// =========================================================================
void DetectionSender::loop() {
  if (!this->isConfigured) return;

}


// ===============================================
// Register the pointers with the object
// ===============================================
void DetectionSender::configure(TURB *tb, TEMP *tp, FLUORO *fl) {
  this->turb   = tb;
  this->temp   = tp;
  this->fluoro = fl;

  this->isConfigured = true;
}


// =========================================================================
// sendLocation - Add a packet with the current location data to the Tx
//                queue.
// =========================================================================
bool DetectionSender::sendSensorData() {

  if (newSensorData(this->temp, this->temp_last_access)) {
    float temp_val = temp->getTempOut();
    
    // If the data is valid, create the packet
    if (temp_val != -1) {
      Temperature *tempPkt = new Temperature();
      tempPkt->addVal(temp_val);
      this->packet_handler->queuePacket(tempPkt);
    }
  }
}


bool DetectionSender::newSensorData(TimedLoop* s, unsigned long int last_run) {
  return s->getLastRuntime() > last_run;
}

#endif