#ifndef GPS_COORD
#define GPS_COORD

// ==================
// Type definition
// ==================
struct coord {
  bool   isValid = false;
  double lat;
  double lng;
};

#endif