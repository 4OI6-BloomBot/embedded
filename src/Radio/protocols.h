/*
  Protocol structure definitions
*/

#ifndef PROTOCOL_H
#define PROTOCOL_H

// ===============================
// Const definitions
// ===============================
#define DATA_ARR_SIZE 31


// ============================================
// Protocol base structure. The size of the
// structure cannot exceed 32-bytes (Tx 
// module constraint).
//  id:   Byte (8-bits), 0 --> 255
//  data: Byte array (3 entries) 
//        Array of values associated with the
//        protocol
// ============================================
struct protocol {
  public:
    // Transmitted values
    byte id;
    byte data[DATA_ARR_SIZE];

    // Constructor
    protocol(byte id) : id(id) {};

    // ===============================
    // addVal - Add data to the array
    // ===============================
    bool addVal(float val) {
      // Calc the size of the data
      int size = sizeof(val);

      // Return false if there is no room in the array
      if ((data_count + size) > DATA_ARR_SIZE) return false;
      
      // Copy the data to the array
      memcpy(data + data_count, (byte *) (& val), size);
    };

  private:
    // Helper var
    byte data_count = 0;
};


// ===================================
// Location protocol (id = 1)
// ===================================
struct location : protocol {
  location() : protocol(1) {};
};

#endif