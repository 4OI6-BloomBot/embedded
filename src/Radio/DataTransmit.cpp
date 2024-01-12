/*
  Wrapper class for the NEO-6M GPS.
*/

#ifndef DATA_TX_CPP
#define DATA_TX_CPP

// Includes
#include "DataTransmit.h"


// ====================
// Static declaration
// ====================
protocol *packets[PACKET_QUEUE_LEN];


// ========================================================
// DataTransmit - Constructor
// ========================================================
DataTransmit::DataTransmit() {
}


// ==============================================
// queuePacket() - Add a packet to the Tx queue
// ==============================================
bool DataTransmit::queuePacket(protocol packet) {
  // TODO: Implement
}

#endif