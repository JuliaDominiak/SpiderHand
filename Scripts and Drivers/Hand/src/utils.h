#include "Arduino.h"

// https://forum.arduino.cc/t/arduino-map-function-for-float-values/112888/4
template <class T>
T map_Generic(T x, T in_min, T in_max, T out_min, T out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template <class T>
T clamp_Generic(T x, T min, T max){
  if (x <= min){
    return min;
  }
  if (x >= max){
    return max;
  }
  return x;
}