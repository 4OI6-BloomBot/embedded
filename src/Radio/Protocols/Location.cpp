/*
  Location protocol struct definitions
*/

#ifndef LOCATION_PROTOCOL_CPP
#define LOCATION_PROTOCOL_CPP

// Includes
#include "Protocol.h"

// ==============================
// Initialize static variable
// ==============================
int Location::currentID = 0;


// ====================================================
// Constructor - Update the static ID and apply it to 
//               the pkt.
// ====================================================
Location::Location() : Protocol(1) {
  Location::currentID++;
  this->setLocationID();
}


// ====================================================
// Add the values from the coord struct to the Location
// packet
// ====================================================
bool Location::setLocation(coord *location) {
  if (addVal(location->lat) && addVal(location->lng)) 
    return true;
  
  return false;
}

#endif