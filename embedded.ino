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
#include "src/Radio/DetectionSender.h"
#include "src/Pathing/Pathing.h"

// =====================================================
// Defines
// TODO: Move me to a config header file
// =====================================================
#define DEBUG

// #define NO_RADIO_GPS
#define NO_PATHING
// #define NO_DETECT

// =====================================================
// Variable Declaration
// Note: For any classes that extend TimedLoop the
//       NUM_TIMEDLOOP_OBJECTS macro needs to be
//       updated to properly reflect the number of
//       children.
// =====================================================

#ifndef NO_PATHING
  MotorController test(7, 8, 9);
  SONIC           sonic(11, 12);
  PATHING         pathing;
#endif

#ifndef NO_RADIO_GPS
  Radio           rf(10, 9, 2);
  GPS             gps(6, 7);
  PacketHandler   packet_handler(&rf, &gps);
  DetectionSender detection_sender(&packet_handler);
  LocationSender  location_sender(&gps, &packet_handler);
#endif

#ifndef NO_DETECT
  #ifndef NO_RADIO_GPS
    Detection detect(&packet_handler);
  #else
    Detection detect(nullptr);
  #endif
#endif


// =====================================================
// setup() - Runs once during power-up
// =====================================================
void setup() {
  #ifdef DEBUG
    Serial.begin(115200);
    Serial.println("%%%%% [RESET] %%%%%");
  #endif

  // ====================================
  // Configure the individual modules
  // ====================================
  #ifndef NO_DETECT
    detect.setup();
  #endif

  #ifndef NO_PATHING
    sonic.setup();
    pathing.setup();
  #endif

  #ifndef NO_RADIO_GPS
    gps.setup();
    packet_handler.setup();
    location_sender.setup();
    detection_sender.configure(detect.getTurb(), detect.getTemp(), detect.getFluoro());
    detection_sender.setup();
    rf.setup();
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
  #ifndef NO_PATHING
  #ifndef NO_DETECT
    if(detect.bloomDetect()){
      pathing.disable();
    } else {
      pathing.enable();
    }
  #endif
  #endif


  TimedLoop::tryEvents();

  // =====================================================
  // Wait for the next scheduled event
  // =====================================================
  // TODO: Change to low power mode/sleep
  delay(TimedLoop::getTimeToNextEvent());

}
