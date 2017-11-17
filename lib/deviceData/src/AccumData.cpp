#include <Arduino.h>
#include "DeviceData.h"
#include "AccumData.h"

void AccumData::setConsumption(float _consumption){
  consumption = _consumption;
}
float AccumData::getConsumption(void){
  return consumption;
}
