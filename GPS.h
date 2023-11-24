/*
  Header for the NEO-6M GPS wrapper class.
*/

#ifndef GPS_H
#define GPS_H

// =================
// Includes
// =================
#include <Arduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>


class GPS {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:
    byte PIN_TX;
    byte PIN_RX;


    // =======================================================
    // setup() - Handles hardware setup after object creation
    // =======================================================
    void setup();

  public:
    // ======================================
    // Constructor: Takes TX & RX pin inputs
    // ======================================
    GPS(byte PIN_TX, byte PIN_RX);

};

#endif