/*
  Header for the NEO-6M GPS wrapper class.
*/

#ifndef DETECTION_SENDER_H
#define DETECTION_SENDER_H

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
#include "../Turb/Turb.h"
#include "../TemperatureSensor/TempSensor.h"
#include "../FluorometerSensor/FluoroSensor.h"
#include "../Radio/Protocols/Protocol.h"
#include "../Radio/PacketHandler.h"

#define DETECTION_SENDER_LOOP_DELAY 100000


class DetectionSender : public TimedLoop {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:

    // =======================================================
    // Private variables
    // =======================================================
    PacketHandler *packet_handler;
    TURB          *turb;
    TEMP          *temp;
    FLUORO        *fluoro;

    unsigned long int turb_last_access;
    unsigned long int temp_last_access;
    unsigned long int fluoro_last_access;
    

    bool isConfigured;


    // =======================================================
    // loop() - Override the loop function from the TimedLoop 
    //          class
    // =======================================================
    void loop() override;

    // Send methods for each sensor
    void sendTemp();
    void sendTurb();
    void sendFluoro();


    bool DetectionSender::newSensorData(TimedLoop* s, unsigned long int last_run);


  public:
    // =======================================================
    // Constructor: Takes TX & RX pin inputs
    //              and optional pointer to packet handler
    // =======================================================
    DetectionSender(PacketHandler *packet_handler);


    // =========================================================
    // configure: Setup the sender with pointers to the sensors
    // =========================================================
    void configure(TURB *tb, TEMP *tp, FLUORO *fl);

};

#endif