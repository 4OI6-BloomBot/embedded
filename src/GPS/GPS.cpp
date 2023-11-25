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
GPS::GPS(byte PIN_TX, byte PIN_RX) {

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

  this->position = new coord();
 
  // Initialize the serial connection
  serial->begin(GPS_BAUD_RATE);

}


// =========================================================================
// pollHardware() - Waits for data from the GPS module and updates the 
//                  parser.
//                  If not enough time has passed since the last poll then
//                  exit with unchanged status.
// =========================================================================
poll_status GPS::pollHardware() {
  long entry_time = millis();

  if (entry_time < (update_time + GPS_MIN_POLLING_TIME_MS))
    return UNCHANGED;

  // ========================================================================
  // Continuously poll the serial connection for data. Once we receive some,
  // update the decoder and return success.
  // If the task runs for too long, return failure.
  // ========================================================================
  while (true) {
    if (gps->encode(serial->read()))
      return SUCCESS;
      
    if (millis() > (entry_time + GPS_RESPONSE_TIMEOUT_MS))
      return FAILURE;
  }
}


// =======================================================
// getLocation() - Returns a struct with updated lat/long
//                 coordinates from the GPS module
// =======================================================
coord * GPS::getLocation() {
  poll_status status = pollHardware();

  if (status == UNCHANGED) {
    position->lat = gps->location.lat();
    position->lng = gps->location.lng();
  }

  if (status != FAILURE) return position;
  else                   return nullptr;
}

#endif