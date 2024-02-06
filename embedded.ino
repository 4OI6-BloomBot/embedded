/*
  embedded.ino

  Entrypoint to the project. Contains setup and main loop.

*/

// =====================================================
// Includes
// =====================================================
#include "src/MotorController/MotorController.h"
#include "src/GPS/GPS.h"
#include "src/GPS/LocationSender.h"
#include "src/SonicSensor/SonicSensor.h"
#include "src/Turb/Turb.h"
#include "src/Radio/Radio.h"
#include "src/Detection/Detection.h"
#include "src/TemperatureSensor/TempSensor.h"
#include "src/Radio/PacketHandler.h"
#include "src/Radio/Protocols/Protocol.h"

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
// SONIC sonic(11,12);
// TURB turb(A0);
// TEMP temp;
Detection      detect;
Radio          rf(10, 9, 4);
GPS            gps(6, 7);
PacketHandler  packet_handler(&rf, &gps);

// LocationSender location_sender(&gps, &packet_handler);

// =====================================================
// setup() - Runs once during power-up
// =====================================================
void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
    Serial.println("%%%%% [RESET] %%%%%");
  #endif

  // =========================
  // Configure the RF module
  // =========================
  rf.setup();
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
  // TODO: Change to low power mode/sleep
  delay(TimedLoop::getTimeToNextEvent());

}
