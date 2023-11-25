/*
  embedded.ino

  Entrypoint to the project. Contains setup and main loop.

*/

// ==========
// Includes
// ==========
#include "src/MotorController/MotorController.h"
#include "src/GPS/GPS.h"

#define DEBUG

// =======================
// Variable Declaration
// =======================
// MotorController test(7, 8, 9);
GPS gps(6, 7);


// ====================================
// setup() - Runs once during power-up
// ====================================
void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
}


// ============================================================
// loop() - Main program loop, runs continuously after setup()
// =============================================================
void loop() {
  gps.getLocation();
}
