/*
  The Detection wrapper class.
*/

#ifndef DETECTION_CPP
#define DETECTION_CPP

// #define TEST
// #define BYPASS_DETECT

// Includes
#include "Detection.h"

// ====================================================
// DETECTION - Constructor for the Detection wrapper class
// ====================================================
Detection::Detection() : TimedLoop(DETECTION_LOOP_DELAY) {
  // Call sensor constructors
  // this->_turb.TURB(A0);
  // TEMP temp(<insert pins>);
  this->_turb.setPIN(A0);
  this->_temp.setPIN(6);

  // After assigning the pins run setup
  setup();
}

// =======================================
// setup() - Initial setup
// =======================================
void Detection::setup() {
  #ifndef TEST
  this->curr_turb  = -1;
  this->prev_turb  = -1;
  this->delta_turb = -1;
  this->curr_temp  = -1;
  this->prev_temp  = -1;
  this->delta_temp = -1;
  #else
  this->curr_turb  = 7;
  this->prev_turb  = 5;
  this->delta_turb = -1;
  this->curr_temp  = 35;
  this->prev_temp  = 26;
  this->delta_temp = -1;
  #endif
  
  this->detect_count = 0; 

}

// =========================================================================
// loop() - Keeps sensor variables up to date
// =========================================================================
void Detection::loop() {
  this->curr_turb = this->_turb.getTurbOut();
  this->curr_temp = this->_temp.getTempOut();

  this->is_detected = monitorDetection();
  #ifdef BYPASS_DETECT
    this->is_detected = 1;
  #endif
  Serial.println(this->is_detected);
  if (this->is_detected) {
    this->_disp.enablePump();
    delay(10000); // 10 sec
    this->_disp.disablePump();
  }
  


  this->prev_temp = this->curr_temp;
  this->prev_turb = this->curr_turb;
}

bool Detection::monitorDetection() {
  if (this->prev_turb != -1 && this->prev_temp != -1) {
    this->delta_turb = this->curr_turb - this->prev_turb;
    this->delta_temp = this->curr_temp - this->prev_temp;
  }

  displayData();

  // =========================================================================
  // Check all sensor conditions for bloom detection
  // Increment detect_count if condition is met
  // =========================================================================
  if (this->delta_turb >= DELTA_TURB_THRESHOLD) {
      // Serial.println("Delta turb threshold exceeded");
      this->detect_count += 1;
  }
  if (this->curr_temp >= TEMP_THRESHOLD) {
      // Serial.println("Temp threshold exceeded");
      this->detect_count += 1;
  }
  if (this->delta_temp >= DELTA_TEMP_THRESHOLD) {
      // Serial.println("Delta temp threshold exceeded");
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

void Detection::displayData() {
  Serial.print("Current Turb: ");
  Serial.print(this->curr_turb);
  Serial.println(" mg/L");
  Serial.print("Previous Turb: ");
  Serial.print(this->prev_turb);
  Serial.println(" mg/L");
  Serial.print("Delta Turb: ");
  Serial.print(this->delta_turb);
  Serial.println(" mg/L");
  
  Serial.print("Current Temp: ");
  Serial.print(this->curr_temp);
  Serial.println(" °C");
  Serial.print("Previous Temp: ");
  Serial.print(this->prev_temp);
  Serial.println(" °C");
  Serial.print("Delta Temp: ");
  Serial.print(this->delta_temp);
  Serial.println(" °C");
}

#endif
