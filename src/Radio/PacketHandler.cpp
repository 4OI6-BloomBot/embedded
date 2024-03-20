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
PacketHandler::PacketHandler(Radio *r, GPS *g, Detection *d) : TimedLoop(PACKET_HANDLER_LOOP_DELAY) {
  this->radio     = r;
  this->gps       = g;
  this->detection = d;

  // Set initial value
  this->tx_queue_cnt = 0;
}


// =======================================================
// setup() - Handles hardware setup after object creation
// =======================================================
void PacketHandler::setup() {
  TimedLoop::setup();
}


// =========================================================
// loop() - Monitor the queues and take action when ready 
// =========================================================
void PacketHandler::loop() {
  genericPacket *pkt;

  // If there are enough packets in the queue, Tx them.
  if (this->tx_queue_cnt >= PACKET_QUEUE_TX_LOW_WATER) {
    int pkt_cnt = this->tx_queue_cnt;
    for (int i = 0; i < pkt_cnt; i++) 
      this->sendPkt();
  }


  // Check if there are packets available in the radio Rx queue
  if (this->radio->getRxQueueCnt() >= PACKET_QUEUE_RX_LOW_WATER) {
    do {
      pkt = this->radio->popRxQueue();
      
      // TODO: Should check for hwID here and discard if mismatches

      this->parseRxData(pkt);

      // Garbage collection
      delete pkt;

    } while(this->radio->getRxQueueCnt() > 0);
  }
}


// =========================================================
// transmitQueue - Attempt to transmit each packet in the
//                 queue.
// =========================================================
void PacketHandler::sendPkt() {
  Protocol *pkt     = this->popTxQueue();
  byte*     payload = pkt->toPayload();;
  
  bool success = this->radio->tx(payload, pkt->getPayloadSize());

  // TODO: Should be more verbose.
  // TODO: Need to handle the error condition (bool result)
  if (success) Serial.println("Tx success");
  else         Serial.println("Tx failed"); 

  // Garbage collection
  delete[] payload;
  delete   pkt;
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


// ==================================================
// parseRxData - Fetch the data from an Rx packet
//               depending on the datatype.
// ==================================================
void PacketHandler::parseRxData(genericPacket *pkt) {
  int sizeCnt = 0;

  // Seems like the best way to handle it right now.
  // There's not going to be too many cases coming from the
  // server, unlike the datatypes coming from the buoy.
  switch (pkt->id) {
    // Config Packet
    case 1:
      int   configID;
      float turbThresh;
      float tempThresh;
      float deltaTempThresh;
      float fluoroThresh;

      memcpy(&configID,        pkt->data,           sizeof(int));
      sizeCnt += sizeof(int);

      memcpy(&turbThresh,      pkt->data + sizeCnt, sizeof(float));
      sizeCnt += sizeof(float);
      
      memcpy(&tempThresh,      pkt->data + sizeCnt, sizeof(float));
      sizeCnt += sizeof(float);
      
      memcpy(&deltaTempThresh, pkt->data + sizeCnt, sizeof(float));
      sizeCnt += sizeof(float);

      memcpy(&fluoroThresh,    pkt->data + sizeCnt, sizeof(float));
      

      Serial.println("Config pkt!");      
      Serial.println(configID);
      Serial.println(fluoroThresh);
      Serial.println(tempThresh);
      Serial.println(deltaTempThresh);
      Serial.println(fluoroThresh);


      // Assign to detection object
      this->detection->delta_turb_threshold = turbThresh;
      this->detection->temp_threshold       = tempThresh;
      this->detection->delta_temp_threshold = deltaTempThresh;
      this->detection->fluoro_threshold     = fluoroThresh;

      break;
    
    // Testing --> location
    case 2:
      float lat, lng;
      Serial.println("Location pkt!");
      memcpy(&lat, pkt->data,     4);
      memcpy(&lng, pkt->data + 4, 4);
            
      Serial.println(lat);
      Serial.println(lng);
      break;
  }
}


// ==============================================
// queuePacket() - Add a packet to the Tx queue
// ==============================================
bool PacketHandler::queuePacket(Protocol *packet) {
  if (this->tx_queue_cnt >= PACKET_QUEUE_TX_LEN)
    return false;

  // Add the current time to the packet
  // Corresponds to approx when the value was grabbed
  packet->time = gps->getTime();

  this->tx_pkt_queue[this->tx_queue_cnt] = packet;
  this->tx_queue_cnt++;
  
  return true;
}

#endif