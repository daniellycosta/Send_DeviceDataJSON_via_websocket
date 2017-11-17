#ifndef IntensityDevice_h
#define IntensityDevice_h

#include <Arduino.h>
#include "AccumData.h"

class IntensityDevice: public AccumData{
private:
double intensity;
public:
  void setIntensity(float _intensity);
  float getIntensity(void);
};

#endif
