/*
  Protocol structure definitions
*/

#ifndef PROTOCOL_H
#define PROTOCOL_H

// ===============================
// Const definitions
// ===============================
#define DATA_ARR_SIZE 29

// ===============================
// Imports
// ===============================
#include <Arduino.h>
#include "../../GPS/Coord.h" // Need to access the coord typedef

struct coord;

// ============================================
// Protocol base structure. The size of the
// structure cannot exceed 32-bytes (Tx 
// module constraint).
//  id:         Byte (8-bits), 0 --> 255
//  hwID:       Byte, unique ID associated w/ the HW
//  locationID: Byte
//  data:       Byte array,
//              Array of values associated with the
//              protocol
// ============================================
struct Protocol {
  public:
    // Transmitted values
    byte id;
    byte hwID;
    byte locationID;
    byte data[DATA_ARR_SIZE];

    // Constructor
    Protocol(byte id);

    // ===============================
    // addVal - Add data to the array
    // ===============================
    bool addVal(float val);

    // =======================================================
    // toPayload() - Create a byte array that can be used by
    //               the radio.
    // =======================================================
    byte* toPayload();

    // =======================================================
    // getPayloadSize() - Returns the size of the data in the
    //                    packet.
    // =======================================================
    int getPayloadSize();

  private:
    // Tracks the mem offset of the data byte array
    byte data_offset = 0;

  protected:
    // =======================================================
    // setLocationID() - Sets the location_id parameter.
    // =======================================================
    void setLocationID();

};


// ===================================
// Location protocol (id = 1)
// ===================================
struct Location : Protocol {
  
  public: 
    Location();

    // ======================================================
    // setLocation - Attempt to add the location data to the 
    //               struct
    // ======================================================
    bool setLocation(coord *location);

    // ======================================================
    // Iterable ID to allow for other data types to reference
    // locations when sending data.
    // ======================================================
    static int currentID;

};


// ===================================
// Temperature protocol (id = 2)
// ===================================
struct Temperature : Protocol {
  
  public: 
    Temperature() : Protocol(2) {};
    
};

#endif