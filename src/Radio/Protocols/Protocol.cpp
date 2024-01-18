/*
  Protocol struct definitions
*/

#ifndef PROTOCOLS_CPP
#define PROTOCOLS_CPP

// Includes
#include "Protocol.h"

// ========================================
// Constructor.
// Set the location at time of creation.
// ========================================
Protocol::Protocol(byte id) {
  this->id = id;
  this->setLocationID();
}


// ====================================================
// addVal() - Add a given value to the packets data 
// TODO: Float declaration is probably not the best
//       in terms of space. Maybe char array?
// ====================================================
bool Protocol::addVal(float val) {
  // Calc the size of the data
  int size = sizeof(val);

  // Return false if there is no room in the array
  if ((this->data_offset + size) > DATA_ARR_SIZE) return false;
      
  // Copy the data to the array
  memcpy(data + this->data_offset, (byte *) (& val), size);

  // Update the data offset
  this->data_offset += size;

  return true;
}


// ====================================================
// Create a payload byte array that can be used 
// by the Radio for Tx
// ====================================================
byte* Protocol::toPayload() {
  byte* payload = new byte[32]; // TODO: Should change hard-coded val to macro?
  int   offset  = 0;

  // Add the protocol ID
  // TODO: Should abstract this repeating code.
  memcpy(payload + offset, (byte *) (&this->id), sizeof(this->id));
  offset += sizeof(this->id);

  // Add the hwID
  memcpy(payload + offset, (byte *) (&this->hwID), sizeof(this->hwID));
  offset += sizeof(this->hwID);

  // Add the location ID
  memcpy(payload + offset, (byte *) (&this->locationID), sizeof(this->locationID));
  offset += sizeof(this->locationID);

  // Add the data
  memcpy(payload + offset, (byte *) (&this->data), this->data_offset);
  offset += this->data_offset;

  return payload;
}


// ====================================================
// Returns the total size of the packet
// ====================================================
int Protocol::getPayloadSize() {
  return sizeof(this->id) + sizeof(this->hwID) + sizeof(this->locationID) + this->data_offset;
}


// =======================================================
// setLocationID() - Sets the location_id parameter.
// TODO: Should have a staic location method to check
//       if the location is still valid (time period).
// =======================================================
void Protocol::setLocationID() {
  this->locationID = Location::currentID;
}

#endif