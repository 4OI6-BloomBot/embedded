/*
  embedded.ino

  Entrypoint to the project. Contains setup and main loop.

*/

// =====================================================
// Includes
// =====================================================
#include "src/MotorController/MotorController.h"
#include "src/GPS/GPS.h"


// =====================================================
// Defines
// TODO: Move me to a config header file
// =====================================================
#define DEBUG


// =====================================================
// Variable Declaration
// Note: For any classes that extend TimedLoop the 
//       NUM_TIMEDLOOP_OBJECTS macro needs to be
//       updated to properly reflect the number of 
//       children.
// =====================================================
// MotorController test(7, 8, 9);
GPS gps(6, 7);


// =====================================================
// setup() - Runs once during power-up
// =====================================================
void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
}


// =====================================================
// loop() - Main program loop, runs continuously
//          after setup()
// =====================================================
void loop() {

  // =====================================================
  // Check each of the timed objects and run their loops
  // if it is time.
  // =====================================================
  TimedLoop::tryEvents();
  
  // =====================================================
  // Wait for the next scheduled event
  // =====================================================
  // TODO: Change to low power mode enable/sleep
  delay(TimedLoop::getTimeToNextEvent());

}
