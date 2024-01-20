/*
  Wrapper class for the NEO-6M GPS.
*/

#ifndef RADIO_CPP
#define RADIO_CPP

// Includes
#include "Radio.h"


// TODO: Move me and review this
byte tx_addr[6] = "1SNSR";
byte rx_addr[6] = "2SNSR";

// ====================================================
// Radio - Constructor for the radio module wrapper
// ====================================================
Radio::Radio(byte PIN_CE, byte PIN_CSN) {

  // Assign class variables 
  this->PIN_CE  = PIN_CE;
  this->PIN_CSN = PIN_CSN;

  // Create new RF24 object
  this->rf24 = new RF24(PIN_CE, PIN_CSN);

}


// =======================================
// setup() - Configure the RF24 radio
// =======================================
void Radio::setup() {

  // Configure the radio
  // TODO: Review what's being done here
  rf24->begin();
  rf24->enableDynamicPayloads();
  rf24->setAutoAck(true);                 
  rf24->setPALevel(NRF24_PA_LEVEL);
  rf24->setRetries(NRF24_RETRY_DELAY, NRF24_RETRY_COUNT);              
  rf24->setDataRate(NRF24_DATA_RATE);          
  rf24->setChannel(NRF24_CHANNEL);
  rf24->setCRCLength(NRF24_CRC_LENGTH);
  rf24->setPayloadSize(NRF24_PAYLOAD_SIZE);
  rf24->openWritingPipe(tx_addr);  
  rf24->openReadingPipe(1, rx_addr);
  // rf24->stopListening();

}


// ==========================================================
// Transmit a passed payload
// TODO: Should probably add some checks and logic here
// ==========================================================
bool Radio::tx(byte* payload, int offset) {
  return rf24->write(payload, offset);
}


void Radio::testReceive() {
  if(rf24->available()) {
    rf24->read(&rxpayload, sizeof(rxpayload));
    Serial.println(rxpayload.id);
    Serial.println(rxpayload.temperature);
    Serial.println(rxpayload.humidity);
  }
}

#endif