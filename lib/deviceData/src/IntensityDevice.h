#ifndef IntensityDevice_h
#define IntensityDevice_h

#include <Arduino.h>
#include "InstantData.h"

class IntensityDevice: public InstantData{
private:
double intensity;
public:
  void setIntensity(float _intensity);
  float getIntensity(void);
};

#endif
