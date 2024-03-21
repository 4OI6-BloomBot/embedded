/*
  Class to manage packaging and sending location data.
*/

#ifndef DETECTION_SENDER_CPP
#define DETECTION_SENDER_CPP

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
  this->turb_last_access   = 0;
  this->temp_last_access   = 0;
  this->fluoro_last_access = 0;
}

// =========================================================================
// loop - TimedLoop override
// =========================================================================
void DetectionSender::loop() {
  if (!this->isConfigured) return;

  this->sendTemp();
  this->sendTurb();
  this->sendFluoro();
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


// =============================================================
// sendTemp - Get data from the temp sensor and queue a packet
//            TODO: These methods are repeat code. Should be 
//                  combined into a single method.
//            TODO: The sensors are repeating methods/code but
//                  do not have a parent class. Should add one.
// =============================================================
void DetectionSender::sendTemp() {
  if (newSensorData(this->temp, this->temp_last_access)) {
    this->temp_last_access = millis();
    
    float val = temp->getTempOut();

    // If the data is valid, create the packet
    if (val != -1) {
      Temperature *pkt = new Temperature();
      pkt->addVal(val);
      this->packet_handler->queuePacket(pkt);
    }
  }
}


// =============================================================
// sendTurb - Get data from the temp sensor and queue a packet
// =============================================================
void DetectionSender::sendTurb() {
  if (newSensorData(this->temp, this->turb_last_access)) {
    this->turb_last_access = millis();
    
    float val = turb->getTurbOut();

    // If the data is valid, create the packet
    if (val != -1) {
      Turbidity *pkt = new Turbidity();
      pkt->addVal(val);
      this->packet_handler->queuePacket(pkt);
    }
  }
}


// =============================================================
// sendTemp - Get data from the temp sensor and queue a packet
// =============================================================
void DetectionSender::sendFluoro() {
  if (newSensorData(this->fluoro, this->fluoro_last_access)) {
    this->fluoro_last_access = millis();
    
    float val = fluoro->getFluoroOut();

    // If the data is valid, create the packet
    if (val != -1) {
      Fluorescence *pkt = new Fluorescence();
      pkt->addVal(val);
      this->packet_handler->queuePacket(pkt);
    }
  }
}


// ==========================================================
// Return true if the sensor has been updated since we last
// sent a value.
// ==========================================================
bool DetectionSender::newSensorData(TimedLoop* s, unsigned long int last_run) {
  return s->getLastRuntime() > last_run;
}

#endif