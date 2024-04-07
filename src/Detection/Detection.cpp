/*
  The Detection wrapper class.
*/

#ifndef DETECTION_CPP
#define DETECTION_CPP

// #define BYPASS_DETECT
// #define DISABLE_LED

#define NO_LOGS

// Includes
#include "Detection.h"

void delimeter() {
  Serial.println("====================================");
}

// ====================================================
// DETECTION - Constructor for the Detection wrapper class
// ====================================================
Detection::Detection(PacketHandler *p) : TimedLoop(DETECTION_LOOP_DELAY) {
  // Call sensor constructors
  this->_turb.setPIN(TURB_PIN_OUT);
  this->_temp.setPIN(TEMP_PIN_OUT);
  this->_fluoro.setPIN(FLUORO_PIN_OUT);

  this->packet_handler = p;

}

// =======================================
// setup() - Initial setup
// =======================================
void Detection::setup() {
  // Call TimedLoop setup
  TimedLoop::setup();

  // Call dispersion setup
  this->_disp.setup(this->packet_handler);

  // Call sensor setups
  this->_fluoro.setup();
  this->_temp.setup();
  this->_turb.setup();

  resetSensorData();
  
  this->detect_count  = 0; 
  // this->fluoro_count  = 0;
  this->en_pump       = 1;
  this->en_sensor     = 1;

  // Turn LED on for fluorometer
  #ifndef DISABLE_LED
    this->_fluoro.enableLED();
  #endif

}

// =========================================================================
// loop() - Keeps sensor variables up to date
// =========================================================================
void Detection::loop() {
  this->curr_turb   = this->_turb.getTurbOut();
  this->curr_temp   = this->_temp.getTempOut();
  this->curr_fluoro = this->_fluoro.getFluoroOut();

  // Update parameters if there is a reference to the packet_handler
  if (this->packet_handler)
    updateConfig(); 

  this->is_detected = monitorDetection();
  #ifdef BYPASS_DETECT
    this->is_detected = 1;
  #endif

  #ifndef NO_LOGS
    Serial.print("is_detected: ");
    Serial.println(this->is_detected);
    Serial.println("=========================================================================");
  #endif

  if (this->en_pump == 1) {
    this->_fluoro.disableLED();                     // LED off during dispersion
    this->_disp.dispersionAlgo(this->is_detected);  // dispersion algo to determine treatment
    this->_fluoro.enableLED();                      // LED on after dispersion
  }
  this->prev_temp   = this->curr_temp;
  this->prev_turb   = this->curr_turb;
  this->prev_fluoro = this->curr_fluoro;

  if (this->is_detected == 1) {
    resetSensorData();
    for (int i = 0; i < TIMEOUT/10; i++) {
      delay(10000); // TIMEOUT in seconds, *1000 converts delay to seconds
      #ifndef NO_LOGS
        Serial.print("TIMEOUT: ");
        Serial.print((i+1)*10);
        Serial.println(" s");
      #endif
    }
    #ifndef NO_LOGS
      delimeter();
    #endif
  }

}


// ============================================================
// Update the detection parameters using data from the server
// ============================================================
void Detection::updateConfig() {
  dispConf *c = this->packet_handler->getConfigParam();

  // If the response is not a nullpointer, update the config param
  if (c) {
    this->turb_threshold          = c->turb_threshold; 
    this->delta_turb_threshold    = c->delta_turb_threshold;
    this->temp_threshold          = c->temp_threshold;
    this->delta_temp_threshold    = c->delta_temp_threshold;
    this->fluoro_threshold        = c->fluoro_threshold;
    this->delta_fluoro_threshold  = c->delta_fluoro_threshold;
  }
}


bool Detection::monitorDetection() {
  if ((this->prev_turb != -1 && this->prev_temp != -1 && this->prev_fluoro != -1) && (this->prev_turb != 0 && this->prev_temp != 0 && this->prev_fluoro != 0)) {
    this->delta_turb    = this->curr_turb   - this->prev_turb;
    this->delta_temp    = this->curr_temp   - this->prev_temp;
    this->delta_fluoro  = this->curr_fluoro - this->prev_fluoro;
  }

  #ifndef NO_LOGS
    displayData();
  #endif

  // =========================================================================
  // Check all sensor conditions for bloom detection
  // Increment detect_count if condition is met
  // =========================================================================
  if (this->curr_turb <= this->turb_threshold) {
      this->detect_count += 1;
  }
  if (this->delta_turb <= (-1.0)*this->delta_turb_threshold) {
      this->detect_count += 1;
  }
  if (this->curr_temp >= this->temp_threshold) {
      this->detect_count += 1;
  }
  if (this->delta_temp >= this->delta_temp_threshold) {
      this->detect_count += 1;
  }
  if (this->curr_fluoro >= this->fluoro_threshold) {
      this->detect_count += 1;
  }
  if (this->delta_fluoro >= this->delta_fluoro_threshold) {
      this->detect_count += 1;
  }

  // =========================================================================
  // Identify if all conditions met for bloom detection
  // =========================================================================
  if (this->detect_count == IS_DETECTED_THRESHOLD) {
      #ifndef NO_LOGS
        Serial.println("BLOOM DETECTED!!!");
      #endif
      this->detect_count = 0;
      return true;
  } else {
      #ifndef NO_LOGS
        Serial.print("Number of conditions detected: ");
        Serial.println(this->detect_count);
      #endif
      this->detect_count = 0;
      return false;
  }


}

// Displays all sensor data
void Detection::displayData() {
  // Turbidity Data
  Serial.print("Current Turb: ");
  Serial.print(this->curr_turb);
  Serial.println(" V");
  Serial.print("Previous Turb: ");
  Serial.print(this->prev_turb);
  Serial.println(" V");
  Serial.print("Delta Turb: ");
  Serial.print(this->delta_turb);
  Serial.println(" V");
  
  // Temperature Data
  Serial.print("Current Temp: ");
  Serial.print(this->curr_temp);
  Serial.println(" °C");
  Serial.print("Previous Temp: ");
  Serial.print(this->prev_temp);
  Serial.println(" °C");
  Serial.print("Delta Temp: ");
  Serial.print(this->delta_temp);
  Serial.println(" °C");

  // Fluorometer Data
  Serial.print("Current Fluoro: ");
  Serial.print(this->curr_fluoro);
  Serial.println(" ");
  Serial.print("Previous Fluoro: ");
  Serial.print(this->prev_fluoro);
  Serial.println(" ");
  Serial.print("Delta Fluoro: ");
  Serial.print(this->delta_fluoro);
  Serial.println(" ");

  delimeter();
}

// Disables dispersion algo and force disables pump
void Detection::disablePump() {
  this->en_pump = 0;
  this->_disp.disablePump();
}

// Disables all sensors, temp, turb and fluoro
void Detection::disableAllSensors() {
  this->en_sensor = 0;
  this->_temp.disableSensor();
  this->_turb.disableSensor();
  this->_fluoro.disableSensor();
}

void Detection::resetSensorData() {
  this->curr_turb     = -1;
  this->prev_turb     = -1;
  this->delta_turb    = -1;
  this->curr_temp     = -1;
  this->prev_temp     = -1;
  this->delta_temp    = -1;
  this->curr_fluoro   = -1;
  this->prev_fluoro   = -1;
  this->delta_fluoro  = -1;
}

bool Detection::bloomDetect() {
  return this->is_detected;
}


// ===============================
// Access methods for the sensors          
// ===============================
TURB* Detection::getTurb() {
  return &_turb;
}

TEMP* Detection::getTemp() {
  return &_temp;
}

FLUORO* Detection::getFluoro() {
  return &_fluoro;
}

#endif
