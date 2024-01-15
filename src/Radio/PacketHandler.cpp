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
PacketHandler::PacketHandler() : TimedLoop(PACKET_HANDLER_LOOP_DELAY) {
  this->tx_queue_cnt = 0;
}

// =========================================================
// loop() - Monitor the queues and take action when ready 
// =========================================================
void PacketHandler::loop() {
  if (this->tx_queue_cnt >= PACKET_QUEUE_TX_LOW_WATER) {
    // Transmit pkts 
  }
}


// ==============================================
// queuePacket() - Add a packet to the Tx queue
// ==============================================
bool PacketHandler::queuePacket(Protocol *packet) {
  if (this->tx_queue_cnt >= PACKET_QUEUE_TX_LEN)
    return false;

  this->tx_pkt_queue[this->tx_queue_cnt] = packet;
  this->tx_queue_cnt++;
  
  return true;
}

#endif