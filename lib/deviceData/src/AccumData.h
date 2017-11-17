#ifndef AccumData_h
#define AccumData_h

#include <Arduino.h>
#include "DeviceData.h"

class AccumData: public DeviceData{
private:
double consumption;

public:
  void setConsumption(float _consumption);
  float getConsumption(void);
};

#endif
