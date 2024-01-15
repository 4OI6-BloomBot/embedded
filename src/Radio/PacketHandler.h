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
#include "Protocols.h"


// ====================
// Parameters
// ====================
#define PACKET_QUEUE_LEN 10


class PacketHandler {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:

  public:  
    // ======================================
    // Constructor:
    // ======================================
    PacketHandler();


    // =======================================================
    // queuePacket - Adds a packet to the Tx queue
    // =======================================================
    static bool queuePacket(protocol packet);

};

#endif