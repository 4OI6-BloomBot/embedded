/*
  Wrapper class for the NEO-6M GPS.
*/

#ifndef GPS_CPP
#define GPS_CPP

// Includes
#include "GPS.h"
#include "../Radio/PacketHandler.h"

// ====================================================
// GPS - Constructor for the NEO-6M GPS wrapper class.
// ====================================================
GPS::GPS(byte PIN_TX, byte PIN_RX) : TimedLoop(GPS_LOOP_DELAY) {

  // Assign class variables 
  this->PIN_TX = PIN_TX;
  this->PIN_RX = PIN_RX;

  // After assigning the pins run setup
  setup();
}

GPS::GPS(byte PIN_TX, byte PIN_RX, PacketHandler *p_handler) : GPS(PIN_TX, PIN_RX) {
  this->packet_handler = p_handler;
}

// =======================================
// setup() - Configure the pin directions
// =======================================
void GPS::setup() {
  
  // Create new objects and add to pointers
  this->gps    = new TinyGPSPlus();
  this->serial = new SoftwareSerial(PIN_RX, PIN_TX);
 
  // Initialize the serial connection
  serial->begin(GPS_BAUD_RATE);

}


time_t* GPS::getTime() {
  
}


// =========================================================================
// loop() - Waits for data from the GPS module and updates the parser.
// =========================================================================
void GPS::loop() {
  long int entry_time = millis();

  // Check the serial connection for a set period
  while (millis() < entry_time + GPS_POLLING_TIME_MS) {
    
    // Need a small delay to reliably get serial data
    delay(5);
    
    if (gps->encode(serial->read())) {
      last_update_time = millis();
        
      // TODO: Should we send every update, or just to correlate w/ other data?
      this->sendLocation();
      
      return;
    }
  }
}


// =======================================================
// getLocation() - Returns a struct with updated lat/long
//                 coordinates from the GPS module
//                 If the data is too old or not available
//                 a null pointer is returned.
// =======================================================
coord* GPS::getLocation() {
  coord *current_pos = new coord();

  if (millis() > (last_update_time + GPS_VALID_PERIOD))
    return nullptr;

  // Check that the data in the GPS parser is valid
  if (gps->location.isValid()) {
    current_pos->lat = gps->location.lat();
    current_pos->lng = gps->location.lng();

    return current_pos;
  }

  return nullptr;
}


// =========================================================================
// sendLocation - Add a packet with the current location data to the Tx
//                queue.
// =========================================================================
bool GPS::sendLocation() {
  coord *data = getLocation();

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