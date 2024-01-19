/*
  Class to manage packaging and sending location data.
*/

#ifndef LOCATION_SENDER_CPP
#define LOCATION_SENDER_CPP

// Includes
#include "LocationSender.h"
#include "GPS.h"
#include "../Radio/PacketHandler.h"

// =========================================================================
// Constructor
// =========================================================================
LocationSender::LocationSender(GPS *gps, PacketHandler *packet_handler) : TimedLoop(LOCATION_SENDER_LOOP_DELAY) {
  this->gps            = gps;
  this->packet_handler = packet_handler;
}

// =========================================================================
// loop - TimedLoop override
//        TODO: Need to check if the location has updated before
//              sending.
// =========================================================================
void LocationSender::loop() {
    this->sendLocation();
}


// =========================================================================
// sendLocation - Add a packet with the current location data to the Tx
//                queue.
// =========================================================================
bool LocationSender::sendLocation() {
  coord *data = gps->getLocation();

  // Stop if the GPS data doesn't exist
  if (!data) return false;

  // Create a new packet and add data
  Location *packet = new Location();
  if (!packet->setLocation(data)) return false;

  // Garbage collection
  delete data;

  return this->packet_handler->queuePacket(packet);
}

#endif