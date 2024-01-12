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
Radio::Radio(byte PIN_CE, byte PIN_CSN) : TimedLoop(RADIO_LOOP_DELAY) {

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
// Temp to test Tx. Compatible with starter file from repo:
// https://github.com/bjarne-hansen/py-nrf24/tree/master
// ==========================================================
void Radio::testSend() {
  byte  protocol = 1;
  float temp     = 10.2;
  float humidity = 1.4;
  
  int offset = 0;

  // Copy the value (normally this was passed in as a param)
  // to the 32 bit payload. Update the offset so that it's all
  // side by side in mem.
  // We can define a couple of protocols for the data we're 
  // sending:
  //  1. Location
  //  2. Sensor data
  //  3. Treatments
  //  4. Status (power, config, etc)
  memcpy(payload + offset, (byte *) (&protocol), sizeof(protocol));
  offset += sizeof(protocol);

  memcpy(payload + offset, (byte *) (&temp), sizeof(temp));
  offset += sizeof(temp);

  memcpy(payload + offset, (byte *) (&humidity), sizeof(humidity));
  offset += sizeof(humidity);

  if (rf24->write(payload, offset)) Serial.println("Sent OK");
  else                              Serial.println("Not sent");

}

void Radio::testReceive() {
  if(rf24->available()) {
    rf24->read(&rxpayload, sizeof(rxpayload));
    Serial.println(rxpayload.id);
    Serial.println(rxpayload.temperature);
    Serial.println(rxpayload.humidity);
  }


}


// =========================================================================
// loop() -
// =========================================================================
void Radio::loop() {
  rf24->stopListening();
  testSend();
  delay(10); 
  rf24->startListening();
  testReceive();

}

#endif