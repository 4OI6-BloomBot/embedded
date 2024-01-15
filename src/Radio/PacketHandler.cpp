/*
  Wrapper class for the NEO-6M GPS.
*/

#ifndef PACKET_HANDLER_CPP
#define PACKET_HANDLER_CPP

// Includes
#include "PacketHandler.h"


// ====================
// Static declaration
// ====================
protocol *packets[PACKET_QUEUE_LEN];


// ========================================================
// DataTransmit - Constructor
// ========================================================
PacketHandler::PacketHandler() {
}


// ==============================================
// queuePacket() - Add a packet to the Tx queue
// ==============================================
bool PacketHandler::queuePacket(protocol packet) {
  // TODO: Implement
}

#endif