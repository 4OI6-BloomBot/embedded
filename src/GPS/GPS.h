/*
  Header for the NEO-6M GPS wrapper class.
*/

#ifndef GPS_H
#define GPS_H

// ==================================================================
// Includes
//  - TimeLoop:       Allows for scheduling periodic polling of
//                    the GPS module
//  - TinyGPS++:      Helps to parse NMEA data that is output from 
//                    the GPS module
//  - SoftwareSerial: Required to interface with the GPS module
// ==================================================================
#include <Arduino.h>
#include "../TimedLoop/TimedLoop.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>


// ==================
// Parameter defines
// ==================
#define GPS_BAUD_RATE       9600
#define GPS_VALID_PERIOD    300000 // Period of time that the GPS data is good for (5 mins)
#define GPS_LOOP_DELAY      5000   // The wait period between main loop runs/polling for a new location
#define GPS_POLLING_TIME_MS 1000   // The period that will wait for a response from the GPS module


// ==================
// Type definition
// ==================
struct coord {
  double lat;
  double lng;
};


class GPS : public TimedLoop {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:
    byte PIN_TX;
    byte PIN_RX;

    unsigned long int last_update_time;

    TinyGPSPlus    * gps;
    SoftwareSerial * serial;


    // =======================================================
    // loop() - Override the loop function from the TimedLoop 
    //          class
    // =======================================================
    void loop() override;

    // =======================================================
    // setup() - Handles hardware setup after object creation
    // =======================================================
    void setup();


  public:
    // ======================================
    // Constructor: Takes TX & RX pin inputs
    // ======================================
    GPS(byte PIN_TX, byte PIN_RX);

    // ===============================
    // getLocation: Accessor method
    // ===============================
    coord * getLocation();

};

#endif