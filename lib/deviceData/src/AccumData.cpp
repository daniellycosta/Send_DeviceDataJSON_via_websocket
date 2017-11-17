#include <Arduino.h>
#include "AccumData.h"

void AccumData::setConsumption(float _consumption){
  consumption = _consumption;
}
float AccumData::getConsumption(void){
  return consumption;
}
