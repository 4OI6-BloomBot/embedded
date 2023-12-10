/*
  Wrapper class for the NEO-6M GPS.
*/

#ifndef GPS_CPP
#define GPS_CPP

// Includes
#include "GPS.h"

// ====================================================
// GPS - Constructor for the NEO-6M GPS wrapper class.
// ====================================================
GPS::GPS(byte PIN_TX, byte PIN_RX) : TimedLoop(GPS_POLLING_TIME_MS) {

  // Assign class variables 
  this->PIN_TX = PIN_TX;
  this->PIN_RX = PIN_RX;

  // After assigning the pins run setup
  setup();
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


// =========================================================================
// loop() - Waits for data from the GPS module and updates the parser.
// =========================================================================
void GPS::loop() {
  if (gps->encode(serial->read()))
    last_update_time = millis();    
}


// =======================================================
// getLocation() - Returns a struct with updated lat/long
//                 coordinates from the GPS module
//                 If the data is too old or not available
//                 a null pointer is returned.
// =======================================================
coord * GPS::getLocation() {
  coord current_pos;

  if (millis() > (last_update_time + GPS_VALID_PERIOD))
    return nullptr;

  // Check that the data in the GPS parser is valid
  if (gps->location.isValid()) {
    current_pos.lat = gps->location.lat();
    current_pos.lng = gps->location.lng();

    return &current_pos;
  }
   
  return nullptr;
}

#endif