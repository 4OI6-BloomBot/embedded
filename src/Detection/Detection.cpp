/*
  The Detection wrapper class.
*/

#ifndef DETECTION_CPP
#define DETECTION_CPP

// #define BYPASS_DETECT
// #define DISABLE_LED

// Includes
#include "Detection.h"

void delimeter() {
  Serial.println("====================================");
}

// ====================================================
// DETECTION - Constructor for the Detection wrapper class
// ====================================================
Detection::Detection() : TimedLoop(DETECTION_LOOP_DELAY) {
  // Call sensor constructors
  this->_turb.setPIN(TURB_PIN_OUT);
  this->_temp.setPIN(TEMP_PIN_OUT);
  this->_fluoro.setPIN(FLUORO_PIN_OUT);

  // After assigning the pins run setup
  setup();
}

// =======================================
// setup() - Initial setup
// =======================================
void Detection::setup() {
  this->curr_turb     = -1;
  this->prev_turb     = -1;
  this->delta_turb    = -1;
  this->curr_temp     = -1;
  this->prev_temp     = -1;
  this->delta_temp    = -1;
  this->curr_fluoro   = -1;
  this->prev_fluoro   = -1;
  this->delta_fluoro  = -1;
  
  this->detect_count  = 0; 
  this->fluoro_count  = 0;
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

  // Serial.println(this->fluoro_count);
  // Serial.println(this->curr_fluoro);
  if (this->fluoro_count < 10) {
    this->fluoro_arr[this->fluoro_count] = this->curr_fluoro;
  }
  else {
    this->fluoro_count = 0;
    float fluoro_avg = 0.0;
    for (int i = 0; i < 10; i++) {
      fluoro_avg += this->fluoro_arr[i];
    }
    fluoro_avg = fluoro_avg/10;
    // Serial.print("Fluoro Avg: ");
    // Serial.println(fluoro_avg);
  }
  this->fluoro_count += 1;

  this->is_detected = monitorDetection();
  #ifdef BYPASS_DETECT
    this->is_detected = 1;
  #endif
  Serial.print("is_detected: ");
  Serial.println(this->is_detected);
  delimeter();

  if (this->en_pump == 1) {
    this->_disp.dispersionAlgo(is_detected);
  }
  this->prev_temp   = this->curr_temp;
  this->prev_turb   = this->curr_turb;
  this->prev_fluoro = this->curr_fluoro;
}

bool Detection::monitorDetection() {
  if ((this->prev_turb != -1 && this->prev_temp != -1 && this->prev_fluoro != -1) && (this->prev_turb != 0 && this->prev_temp != 0 && this->prev_fluoro != 0)) {
    this->delta_turb    = this->curr_turb   - this->prev_turb;
    this->delta_temp    = this->curr_temp   - this->prev_temp;
    this->delta_fluoro  = this->curr_fluoro - this->prev_fluoro;
  }

  displayData();

  // =========================================================================
  // Check all sensor conditions for bloom detection
  // Increment detect_count if condition is met
  // =========================================================================
  if (this->curr_turb <= TURB_THRESHOLD) {
      this->detect_count += 1;
  }
  if (this->delta_turb <= (-1.0)*DELTA_TURB_THRESHOLD) {
      this->detect_count += 1;
  }
  if (this->curr_temp >= TEMP_THRESHOLD) {
      this->detect_count += 1;
  }
  if (this->delta_temp >= DELTA_TEMP_THRESHOLD) {
      this->detect_count += 1;
  }
  if (this->curr_fluoro >= FLUORO_THRESHOLD) {
      this->detect_count += 1;
  }

  // =========================================================================
  // Identify if all conditions met for bloom detection
  // =========================================================================
  if (this->detect_count == IS_DETECTED_THRESHOLD) {
      Serial.println("BLOOM DETECTED!!!");
      this->detect_count = 0;
      return true;
  } else {
      Serial.print("Number of conditions detected: ");
      Serial.println(this->detect_count);
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

bool Detection::bloomDetect() {
  return this->is_detected;
}

#endif
