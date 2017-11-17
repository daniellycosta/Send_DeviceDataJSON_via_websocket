#include <Arduino.h>
#include "IntensityDevice.h"

void IntensityDevice::setIntensity(float _intensity){
  intensity = _intensity;
}

float IntensityDevice::getIntensity(void){
  return intensity;
}
