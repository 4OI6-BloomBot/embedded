/*
  Location protocol struct definitions
*/

#ifndef LOCATION_PROTOCOL_CPP
#define LOCATION_PROTOCOL_CPP

// Includes
#include "Protocols.h"

// ==============================
// Initialize static variable
// ==============================
int Location::location_id = 0;


// ====================================================
// Add the values from the coord struct to the Location
// packet
// ====================================================
bool Location::setLocation(coord *location) {
  if (addVal(location->lat) && addVal(location->lng)) 
    return true;
  
  return false;
}

// ======================================================
// addLocationID - Attempt to add the location ID to the 
//                 packet.
// ======================================================
bool addLocationID(Protocol *pkt) {
  pkt->addVal(Location::location_id);
  return true;
}

#endif