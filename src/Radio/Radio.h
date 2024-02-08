/*
  Header for the RF24 900MHz radio module
*/

#ifndef RADIO_H
#define RADIO_H

// ==================================================================
// Includes
//  - TimeLoop: Allows for scheduling when to transmit packets from
//              the queue.
//  - RF24:     Allows for setup/communication with the RF module 
// ==================================================================
#include <Arduino.h>
#include "../TimedLoop/TimedLoop.h"
#include <RF24.h>
#include "genericPacket.h"


// ==================
// Parameter defines
// ==================

// TODO: Review these params
#define NRF24_CHANNEL         100          // 0 ... 125
#define NRF24_CRC_LENGTH      RF24_CRC_16  // RF24_CRC_DISABLED, RF24_CRC_8, RF24_CRC_16 for 16-bit
#define NRF24_DATA_RATE       RF24_250KBPS // RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
#define NRF24_DYNAMIC_PAYLOAD 1
#define NRF24_PAYLOAD_SIZE    32           // Max. 32 bytes.
#define NRF24_PA_LEVEL        RF24_PA_MIN  // RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX    
#define NRF24_RETRY_DELAY     5            // Delay bewteen retries, 1..15.  Multiples of 250µs.
#define NRF24_RETRY_COUNT     15           // Number of retries, 1..15.

#define PROTOCOL 0x01                      // 0x01 (byte), temperature (float), humidity (float)


class Radio {
  
  // ==================================================================
  // Private fields. 
  // ==================================================================
  private:
    byte PIN_CSN;
    byte PIN_CE;
    byte PIN_IRQ;

    RF24 *rf24;

    byte payload[32];

    static Radio * rxStaticObj;


    // ================================================================
    // handleInterruptTrigger() - Static method that calls the
    //                            handleRxInterrupt method on the static
    //                            radio object.
    // ================================================================
    static void handleInterruptTrigger();


    // ================================================================
    // handleRxInterrupt() - Function to run when an handleRxInterrupt
    //                       is sent by the radio module.
    // ================================================================
    void handleRxInterrupt();


    // ======================================================
    // Testing method for Radio.
    // TODO: Going to need to think through how to structure
    // this considering the struct. of the sensor classes 
    // and such.
    // ======================================================
    genericPacket* getRxData();

  public:  
    // ======================================
    // Constructor: Takes RF24 pins
    // ======================================
    Radio(byte PIN_CE, byte PIN_CSN, byte PIN_IRQ);

    // =======================================================
    // setup() - Handles hardware setup after object creation
    //           Note: Has to happen in the embedded.ino
    //                 setup function or else system hangs.
    // =======================================================
    void setup();

    // =======================================================
    // Transmit a passed byte array
    // =======================================================
    bool tx(byte* payload, int offset);

};

#endif