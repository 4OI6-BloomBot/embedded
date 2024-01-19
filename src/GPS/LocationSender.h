/*
  Header for the NEO-6M GPS wrapper class.
*/

#ifndef LOCATION_SENDER_H
#define LOCATION_SENDER_H

// ==================================================================
// Includes
//  - TimeLoop:       Allows for scheduling periodic polling of
//                    the GPS module
//  - TinyGPS++:      Helps to parse NMEA data that is output from 
//                    the GPS module
//  - SoftwareSerial: Required to interface with the GPS module
// ==================================================================
#include <Arduino.h>
#include "Coord.h"
#include "../TimedLoop/TimedLoop.h"
#include "../Radio/PacketHandler.h"

#define LOCATION_SENDER_LOOP_DELAY 5000


class LocationSender : public TimedLoop {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:

    GPS           *gps;
    PacketHandler *packet_handler;

    // =======================================================
    // loop() - Override the loop function from the TimedLoop 
    //          class
    // =======================================================
    void loop() override;


  public:
    // =======================================================
    // Constructor: Takes TX & RX pin inputs
    //              and optional pointer to packet handler
    // =======================================================
    LocationSender(GPS *gps, PacketHandler *packet_handler);


    // =======================================================
    // sendLocation: Add packet with location to Tx queue
    // =======================================================
    bool sendLocation();

};

#endif