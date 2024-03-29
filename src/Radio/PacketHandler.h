/*
  Header for the class used to handle data Tx/Rx
  through the radio.
*/

#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

// ==================================================================
// Includes
//  - TimedLoop: Required to serve the queues
//  - Protocols: Required to reference the protocol struct type
//  - Radio:     Required to Tx/Rx packets
//  - GPS:       Required to get the time
// ==================================================================
#include <Arduino.h>
#include "../TimedLoop/TimedLoop.h"
#include "Protocols/Protocol.h"
#include "Radio.h"
#include "../GPS/GPS.h"
#include "genericPacket.h"
#include "../Detection/Detection.h"


// ====================
// Parameters
// ====================
#define PACKET_HANDLER_LOOP_DELAY 3000 // Likely use as something to monitor a Tx queue?

#define PACKET_QUEUE_TX_LEN       10
#define PACKET_QUEUE_TX_LOW_WATER 3

#define PACKET_QUEUE_RX_LOW_WATER 1


class PacketHandler : TimedLoop {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:
    Radio     *radio;
    GPS       *gps;
    Detection *detection;

    Protocol *tx_pkt_queue[PACKET_QUEUE_TX_LEN];
    uint16_t tx_queue_cnt;
    uint16_t configID;
    byte     hwID;
    
    // ==================================================
    // loop() - Override loop fn from TimedLoop class.
    //          Monitors queues
    // ==================================================
    void loop() override;


    // ==================================================
    // popTxQueue() - Get a pointer to the first packet
    //                in the queue.
    // ==================================================
    Protocol* popTxQueue();


    // ==================================================
    // sendPkt - Send a packet from the front of the 
    //           Tx queue
    // ==================================================
    bool sendPkt();


    // ==================================================
    // parseRxData - Fetch the data from an Rx packet
    //               depending on the datatype.
    // ==================================================
    void parseRxData(genericPacket*);


  public:  
    // ====================================================
    // Constructor:
    // Requires a pointer to a Radio and detection object
    // ====================================================
    PacketHandler(Radio *radio, GPS *gps, Detection *detection);


    // =======================================================
    // setup() - Handles hardware setup after object creation
    // =======================================================
    void setup();


    // =======================================================
    // queuePacket - Adds a packet to the Tx queue
    // =======================================================
    bool queuePacket(Protocol *packet);

};

#endif