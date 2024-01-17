/*
  Header for the class used to handle transmitting data
  through the radio.
*/

#ifndef DATA_TX_H
#define DATA_TX_H

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


class DataTransmit {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:

  public:  
    // ======================================
    // Constructor:
    // ======================================
    DataTransmit();


    // =======================================================
    // queuePacket - Adds a packet to the Tx queue
    // =======================================================
    static bool queuePacket(protocol packet);

};

#endif