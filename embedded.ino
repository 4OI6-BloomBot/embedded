/*
  embedded.ino

  Entrypoint to the project. Contains setup and main loop.

*/

// ===============
// Config
// ===============
// #define DEBUG;

// ==========
// Includes
// ==========
#include "MotorController.h";

// =======================
// Variable Declaration
// =======================
MotorController test(7, 8, 9);



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
  test.setDirection(FORWARD);
  delay(1000);
  test.setDirection(BACKWARD);
  delay(1000);
}
