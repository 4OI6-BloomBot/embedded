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


// ======================================================
// getTime - Pulls the time from the RTC and returns a
//           time_t obj.
// ======================================================
time_t GPS::getTime() {

  // Make sure we have valid GPS data
  if (!gps->time.isValid() || !gps->date.isValid()) 
    return 0;
  
  TinyGPSDate d = gps->date;
  TinyGPSTime t = gps->time;
  
  // isValid won't necessarily tell us if the data is 
  // correct only that we got something from the module.
  // The GPS will happily report an invalid date. This 
  // guards against using something that is obviously 
  // invalid
  // This isn't ideal, but typically the dates reported
  // are way off (2000, 2008, 2088, etc) so this should be 
  // a decent fix for now.
  // TODO: Not a long term soln. Implement Sam's idea --> wait for position to be valid too.
  if (d.year() <= 2023 || d.year() >= 2030)
    return 0;
  
  // Update the time and account for the timezone
  setTime(t.hour(), t.minute(), t.second(), d.day(), d.month(), d.year());
  
  // The time is being sent as UTC for now. 
  // TODO: Update the server to display the time correctly (per the timezone).
  // TODO: Clean this up once the timezone work has settled down a bit
  // adjustTime(GPS_TIME_OFFSET * SECS_PER_HOUR);


  return now();
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

#endif