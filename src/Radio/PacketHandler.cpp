/*
  Wrapper class for the NEO-6M GPS.
*/

#ifndef PACKET_HANDLER_CPP
#define PACKET_HANDLER_CPP

// Includes
#include "PacketHandler.h"


// ========================================================
// PacketHandler - Constructor
// ========================================================
PacketHandler::PacketHandler(Radio *r) : TimedLoop(PACKET_HANDLER_LOOP_DELAY) {
  this->radio = r;
  
  this->tx_queue_cnt = 0;
}


// =========================================================
// loop() - Monitor the queues and take action when ready 
// =========================================================
void PacketHandler::loop() {
  // If there are enough packets in the queue, Tx them.
  if (this->tx_queue_cnt >= PACKET_QUEUE_TX_LOW_WATER) {
    Protocol *pkt = this->popTxQueue();

    byte* payload = pkt->toPayload();
    bool success  = this->radio->tx(payload, pkt->getPayloadSize());
    
    // TODO: Should be more verbose.
    // TODO: Need to handle the error condition (bool result)
    if (success) Serial.println("Tx success");
    else         Serial.println("Tx failed"); 

    // Garbage collection
    delete[] payload;
    delete   pkt;
  }
}


// =========================================================
// popTxQueue() - Pop the first element from the queue
//                and shift forward the remaining 
//                elements.
// =========================================================
Protocol* PacketHandler::popTxQueue() {
  // Check that there are elements in the queue
  if (this->tx_queue_cnt == 0) return nullptr;

  Protocol *popped = this->tx_pkt_queue[0];

  // Shift the elements in the array up
  for (int i = 0; i < (this->tx_queue_cnt - 1); i++){
    // Account for corner case of full queue
    if (i >= PACKET_QUEUE_TX_LEN) break;

    this->tx_pkt_queue[i] = this->tx_pkt_queue[i + 1];
  }
  this->tx_pkt_queue[this->tx_queue_cnt - 1] = nullptr;

  this->tx_queue_cnt--;

  return popped;
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