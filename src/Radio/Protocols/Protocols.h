/*
  Protocol structure definitions
*/

#ifndef PROTOCOL_H
#define PROTOCOL_H

// ===============================
// Const definitions
// ===============================
#define DATA_ARR_SIZE 30

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
//  id:   Byte (8-bits), 0 --> 255
//  hwID: Byte, unique ID associated w/ the HW
//  data: Byte array,
//        Array of values associated with the
//        protocol
// ============================================
struct Protocol {
  public:
    // Transmitted values
    byte id;
    byte hwID;
    byte data[DATA_ARR_SIZE];

    // Constructor
    Protocol(byte id) : id(id) {};

    // ===============================
    // addVal - Add data to the array
    // ===============================
    bool addVal(float val);

  private:
    // Tracks the mem offset of the data byte array
    byte data_offset = 0;

    byte* toPayload();

    int getPayloadSize();
};


// ===================================
// Location protocol (id = 1)
// ===================================
struct Location : Protocol {
  
  public: 
    Location() : Protocol(1) {};

    // ======================================================
    // setLocation - Attempt to add the location data to the 
    //               struct
    // ======================================================
    bool setLocation(coord *location);
};

#endif