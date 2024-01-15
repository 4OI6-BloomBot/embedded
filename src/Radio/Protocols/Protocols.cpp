/*
  Protocol struct definitions
*/

#ifndef PROTOCOLS_CPP
#define PROTOCOLS_CPP

// Includes
#include "Protocols.h"

// ====================================================
// Protocol 
// ====================================================
bool Protocol::addVal(float val) {
  // Calc the size of the data
  int size = sizeof(val);

  // Return false if there is no room in the array
  if ((data_count + size) > DATA_ARR_SIZE) return false;
      
  // Copy the data to the array
  memcpy(data + data_count, (byte *) (& val), size);
}



bool Location::setLocation(coord *location) {
  if (addVal(location->lat) && addVal(location->lng)) 
    return true;
  
  return false;
}

#endif