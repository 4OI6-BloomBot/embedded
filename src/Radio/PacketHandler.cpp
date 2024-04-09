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
PacketHandler::PacketHandler(Radio *r, GPS *g) : TimedLoop(PACKET_HANDLER_LOOP_DELAY) {
  this->radio     = r;
  this->gps       = g;

  // Set initial value
  this->tx_queue_cnt = 0;
  this->configID     = (uint16_t) - 1;

  // Set per-device
  this->hwID = 0;
  this->config = new dispConf();
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
  int failedPkts = 0, successPkts = 0;

  // If there are enough packets in the queue, Tx them.
  if (this->tx_queue_cnt >= PACKET_QUEUE_TX_LOW_WATER) {
    int pkt_cnt = this->tx_queue_cnt;
    for (int i = 0; i < pkt_cnt; i++) { 
      if (this->sendPkt())  successPkts++;
      else                  failedPkts++;
    }

    // Print results
    if (successPkts > 0) { 
      Serial.print("[INFO] Successfully transmitted ");
      Serial.print(successPkts);
      Serial.println(" packets.");
    } 

    if (failedPkts > 0) {
      Serial.print("[ERROR] Failed to transmit ");
      Serial.print(failedPkts);
      Serial.println(" packets.");
    } 
  }


  // Check if there are packets available in the radio Rx queue
  if (this->radio->getRxQueueCnt() >= PACKET_QUEUE_RX_LOW_WATER) {
    for (int i = 0; i < this->radio->getRxQueueCnt(); i++) {
      pkt = this->radio->getRxQueueIndex(i);
      Serial.println("here2");
      // If the pkt is a nullpointer, break
      if (!pkt) continue;
      
      // Check if the hwID matches the device.
      if (pkt->hwID == this->hwID) {
        this->parseRxData(pkt);
      }

      // Garbage collection
      delete pkt;
    }
    this->radio->resetRxQueue();
  }
}


// =========================================================
// transmitQueue - Attempt to transmit each packet in the
//                 queue.
// =========================================================
bool PacketHandler::sendPkt() {
  Protocol *pkt     = this->popTxQueue();

  // Update the hwID of the packet
  pkt->hwID = this->hwID;
  
  // Convert the packet to bytes and transmit
  byte* payload = pkt->toPayload();;
  bool success  = this->radio->tx(payload, pkt->getPayloadSize());

  // Garbage collection
  delete[] payload;
  delete   pkt;

  return success;
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
      float turbThresh, deltaTurbThresh, tempThresh, deltaTempThresh, fluoroThresh, deltaFluoroThresh;
      bool  skipDetection;

      // Integer from the basestation is 4 bytes long
      // TODO: convert to short on basestaion?
      memcpy(&configID,        pkt->data,           4);
      sizeCnt += 4;

      // If the currrent configuration has already been applied, skip it.
      if (configID == this->configID) return;
      this->configID = configID;

      // Copy the values to the local variables
      memcpy(&tempThresh,        pkt->data + sizeCnt, sizeof(float));
      sizeCnt += sizeof(float);

      memcpy(&deltaTempThresh,   pkt->data + sizeCnt, sizeof(float));
      sizeCnt += sizeof(float);

      memcpy(&turbThresh,        pkt->data + sizeCnt, sizeof(float));
      sizeCnt += sizeof(float);

      memcpy(&deltaTurbThresh,   pkt->data + sizeCnt, sizeof(float));
      sizeCnt += sizeof(float);

      memcpy(&fluoroThresh,      pkt->data + sizeCnt, sizeof(float));    
      sizeCnt += sizeof(float);

      memcpy(&deltaFluoroThresh, pkt->data + sizeCnt, sizeof(float));      
      sizeCnt += sizeof(float);

      memcpy(&skipDetection,     pkt->data + sizeCnt, 1);

      // Print info to the console
      Serial.println("[INFO] Received a new configuration!");      
      Serial.print("Config ID: ");
      Serial.print(configID);
      Serial.print(" | Temperature Threshold: ");
      Serial.print(tempThresh);
      Serial.print(" | Delta Temperature Threshold: ");
      Serial.print(deltaTempThresh);
      Serial.print(" | Turbididty Threshold: ");
      Serial.print(turbThresh);
      Serial.print(" | Delta Turbidity Threshold: ");
      Serial.print(deltaTurbThresh);
      Serial.print(" | Flurometer Threshold: ");
      Serial.print(fluoroThresh);
      Serial.print(" | Delta Flurometer Threshold: ");
      Serial.print(deltaFluoroThresh);
      Serial.print(" | Skip detection: ");
      Serial.println(skipDetection);



      // Assign values to the config object      
      this->config->turb_threshold         = turbThresh;
      this->config->delta_turb_threshold   = deltaTurbThresh;
      this->config->temp_threshold         = tempThresh;
      this->config->delta_temp_threshold   = deltaTempThresh;
      this->config->fluoro_threshold       = fluoroThresh;
      this->config->delta_fluoro_threshold = deltaFluoroThresh;
      this->config->skipDetection          = skipDetection;

      break;
  }
}


// ==========================================================
// Return a pointer to the config object if it is required
// ==========================================================
dispConf* PacketHandler::getConfigParam() {
  if (this->configID == (uint16_t) - 1) return nullptr;

  return this->config;
}


// ==============================================
// queuePacket() - Add a packet to the Tx queue
// ==============================================
bool PacketHandler::queuePacket(Protocol *packet) {
  if (this->tx_queue_cnt >= PACKET_QUEUE_TX_LEN) {
    delete packet;
    return false;
  }

  // Add the current time to the packet
  // Corresponds to approx when the value was grabbed
  packet->time = gps->getTime();

  this->tx_pkt_queue[this->tx_queue_cnt] = packet;
  this->tx_queue_cnt++;
  
  return true;
}

#endif