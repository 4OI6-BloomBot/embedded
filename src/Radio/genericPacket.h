#ifndef GENERIC_PACKET
#define GENERIC_PACKET
  // =========================================
  // General structure for all data received
  // =========================================
  struct genericPacket {
    byte id;
    byte hwID;
    byte data[30];
  };

#endif