/*
  Header for the class used to handle data Tx/Rx
  through the radio.
*/

#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

// ==================================================================
// Includes
//  - Protocols: Required to reference the protocol struct type
// ==================================================================
#include <Arduino.h>
#include "../TimedLoop/TimedLoop.h"
#include "Protocols/Protocols.h"


// ====================
// Parameters
// ====================
#define PACKET_HANDLER_LOOP_DELAY 3000 // Likely use as something to monitor a Tx queue?

#define PACKET_QUEUE_TX_LEN       10
#define PACKET_QUEUE_TX_LOW_WATER 3


class PacketHandler : TimedLoop {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:
    Protocol *tx_pkt_queue[PACKET_QUEUE_TX_LEN];
    uint16_t tx_queue_cnt;
    
    // ==================================================
    // loop() - Override loop fn from TimedLoop class.
    //          Monitors queues
    // ==================================================
    void loop() override;


  public:  
    // ======================================
    // Constructor:
    // ======================================
    PacketHandler();


    // =======================================================
    // queuePacket - Adds a packet to the Tx queue
    // =======================================================
    bool queuePacket(Protocol *packet);

};

#endif