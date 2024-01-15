/*
  Wrapper class for the NEO-6M GPS.
*/

#ifndef PACKET_HANDLER_CPP
#define PACKET_HANDLER_CPP

// Includes
#include "PacketHandler.h"


// ========================================================
// DataTransmit - Constructor
// ========================================================
PacketHandler::PacketHandler() {
  this->tx_queue_cnt = 0;
}


// ==============================================
// queuePacket() - Add a packet to the Tx queue
// ==============================================
bool PacketHandler::queuePacket(protocol packet) {
  // if (tx_pkt_queue)
}

#endif