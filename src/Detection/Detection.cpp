/*
  The Detection wrapper class.
*/

#ifndef DETECTION_CPP
#define DETECTION_CPP

#define TEST

// Includes
#include "Detection.h"

// ====================================================
// DETECTION - Constructor for the Detection wrapper class
// ====================================================
Detection::Detection() : TimedLoop(DETECTION_LOOP_DELAY) {
  // Call sensor constructors
  // this->turb(A0);
  // TEMP temp(<insert pins>);
  // Serial.println("from constructor");
  // Serial.println(temp);

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
    
  // Serial.println("from setup");
    

}

// =========================================================================
// loop() - Keeps sensor variables up to date
// =========================================================================
void Detection::loop() {
  Serial.println("from loop");
  // this->curr_turb = this->turb.getTurb();
  // this->curr_temp = temp.getTemp();
  this->is_detected = monitorDetection();
  Serial.println(this->is_detected);


  // this->prev_temp = this->curr_temp;
  // this->prev_turb = this->curr_temp;
}

bool Detection::monitorDetection() {
  this->delta_turb = this->curr_turb - this->prev_turb;
  this->delta_temp = this->curr_temp - this->prev_temp;

  // =========================================================================
  // Check all sensor conditions for bloom detection
  // Increment detect_count if condition is met
  // =========================================================================
  if (this->delta_turb > DELTA_TURB_THRESHOLD) {
      Serial.println("Delta turb threshold exceeded");
      this->detect_count += 1;
  }
  if (this->curr_temp > TEMP_THRESHOLD) {
      Serial.println("Temp threshold exceeded");
      this->detect_count += 1;
  }
  if (this->delta_temp > DELTA_TEMP_THRESHOLD) {
      Serial.println("Delta temp threshold exceeded");
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

#endif
