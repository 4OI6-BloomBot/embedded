/*
  Wrapper class for the RF24 radio
*/

#ifndef RADIO_CPP
#define RADIO_CPP

// Includes
#include "Radio.h"


// TODO: Move me and review this
byte tx_addr[6] = "1SNSR";
byte rx_addr[6] = "2SNSR";

// Initialize static variable
Radio * Radio::rxStaticObj = nullptr;

// ====================================================
// Radio - Constructor for the radio module wrapper
// ====================================================
Radio::Radio(byte PIN_CE, byte PIN_CSN, byte PIN_IRQ) {

  // Assign class variables 
  this->PIN_CE  = PIN_CE;
  this->PIN_CSN = PIN_CSN;
  this->PIN_IRQ = PIN_IRQ;

  // Create new RF24 object
  this->rf24 = new RF24(PIN_CE, PIN_CSN);

  // Set initial values
  this->rx_queue_cnt = 0;

}


// =======================================
// setup() - Configure the RF24 radio
// =======================================
void Radio::setup() {

  // Configure the radio
  // TODO: Review what's being done here
  rf24->begin();

  // Enable automatic ACK
  rf24->enableDynamicPayloads();
  rf24->setAutoAck(true);                 
  
  rf24->setPALevel(NRF24_PA_LEVEL);
  rf24->setRetries(NRF24_RETRY_DELAY, NRF24_RETRY_COUNT);              
  rf24->setDataRate(NRF24_DATA_RATE);          
  rf24->setChannel(NRF24_CHANNEL);
  rf24->setCRCLength(NRF24_CRC_LENGTH);
  rf24->setPayloadSize(NRF24_PAYLOAD_SIZE);
  
  // Open Tx/Rx addresses on seperate pipes
  rf24->openWritingPipe(tx_addr);  
  rf24->openReadingPipe(1, rx_addr);


  // ==========================
  // Configure Rx interrupt 
  // ==========================
  // Assign this object as the Rx handler
  Radio::rxStaticObj = this;

  // Interrupt pin must be 2 or 3 for Arduino UNO
  if (this->PIN_IRQ < 2 || this->PIN_IRQ > 3)
    Serial.println("[ERROR] Arduino UNO must use pin 2 or 3 for interrupts.");
  
  // This won't work if the wrong pin is set, but it doesn't break anything either.
  // Therefore, not guarding (in case used HW is different from UNO)
  pinMode(this->PIN_IRQ, INPUT);
  attachInterrupt(digitalPinToInterrupt(this->PIN_IRQ), handleInterruptTrigger, FALLING);

  // Configure the interrupt to only trigger on Rx
  rf24->maskIRQ(1, 1, 0);

  rf24->startListening();

}


// ==========================================================
// Transmit a passed payload
// TODO: Should probably add some checks and logic here
// ==========================================================
bool Radio::tx(byte* payload, int offset) {
  return rf24->write(payload, offset);
}


// ==========================================================
// Static method to call the handleRxInterrupt method.
// Required since the attachInterrupt function can't accept
// an object method.
// ==========================================================
void Radio::handleInterruptTrigger() {
  Radio::rxStaticObj->handleRxInterrupt();
}


// ==========================================================
// Handle an interrupt from the radio module
// ==========================================================
void Radio::handleRxInterrupt() {
  // Tx data sent
  // Tx data fail
  // Rx data ready
  bool tx_ds, tx_df, rx_dr;
  Serial.println("[INFO] Packet Received");

  // Clear interrupt and find out what triggered it
  rf24->whatHappened(tx_ds, tx_df, rx_dr);

  // Only case we are expecting to handle is when
  // there is new Rx data to process and there is space
  // to store it.
  if (rx_dr && this->rx_queue_cnt < (PACKET_QUEUE_RX_LEN - 1)) {
    this->rx_pkt_queue[this->rx_queue_cnt] = this->getRxData();
    this->rx_queue_cnt++;
  }

  // TODO: Throw error when tx_ds or tx_df trigger?
}


// ======================================================
// getRxData - Get the data from the radio and return an
//             address to the created struct.
// ======================================================
genericPacket* Radio::getRxData() {
  genericPacket *packet = new genericPacket;

  if(rf24->available()) {
    rf24->read(packet, sizeof(*packet));
    Serial.println(packet->id);
    Serial.println(packet->hwID);
    Serial.println(*packet->data[0]);
  }

  return packet;
}


// =======================================================
// Accessor method for packet count of Rx queue
// =======================================================
int Radio::getRxQueueCnt() {
  return this->rx_queue_cnt;
}

// =======================================================
// popRxQueue - Accessor method for packets in Rx queue
// =======================================================
genericPacket* Radio::popRxQueue() {
    // Check that there are elements in the queue
  if (this->rx_queue_cnt == 0) return nullptr;

  genericPacket *popped = this->rx_pkt_queue[0];

  // Shift the elements in the array up
  for (int i = 0; i < (this->rx_queue_cnt - 1); i++){
    // Account for corner case of full queue
    if (i >= PACKET_QUEUE_RX_LEN) break;

    this->rx_pkt_queue[i] = this->rx_pkt_queue[i + 1];
  }
  this->rx_pkt_queue[this->rx_queue_cnt - 1] = nullptr;

  this->rx_queue_cnt--;

  return popped;
}

#endif