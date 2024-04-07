#ifndef CONFIG_STRUCT
#define CONFIG_STRUCT

// ==================
// Type definition
// ==================
struct dispConf {
  int   configID;
  float turb_threshold;
  float delta_turb_threshold; 
  float temp_threshold;
  float delta_temp_threshold; 
  float fluoro_threshold; 
  float delta_fluoro_threshold; 
  bool  bypass_detect; 
};

#endif