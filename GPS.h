/*
  Header for the NEO-6M GPS wrapper class.
*/

#ifndef GPS_H
#define GPS_H

// ==================================================================
// Includes
//  - TinyGPS++:      Helps to parse NMEA data that is output from 
//                    the GPS module
//  - SoftwareSerial: Required to interface with the GPS module
// ==================================================================
#include <Arduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>


// ==================
// Parameter defines
// ==================
#define GPS_BAUD_RATE           9600
#define GPS_RESPONSE_TIMEOUT_MS 1000 // Timeout to wait for new data from the GPS module
#define GPS_MIN_POLLING_TIME_MS 5000 // The minimum wait before polling for a new position from the GPS


// ==================
// Type definition
// ==================
struct coord {
  double lat;
  double lng;
};

enum poll_status {SUCCESS, FAILURE, UNCHANGED};


class GPS {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:
    byte PIN_TX;
    byte PIN_RX;

    coord * position;
    long    update_time;

    TinyGPSPlus    * gps;
    SoftwareSerial * serial;


    // =======================================================
    // setup() - Handles hardware setup after object creation
    // =======================================================
    void setup();


    // =======================================================
    // pollHardware() - Waits for data from the GPS module 
    //                  and updates the parser.
    // =======================================================
    poll_status pollHardware();


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