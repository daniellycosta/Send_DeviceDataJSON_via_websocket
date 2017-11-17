#ifndef InstantData_h
#define InstantData_h

#include <Arduino.h>
#include "DeviceData.h"

template <class Type> class InstantData: public DeviceData{
private:
Type value;
public:
  void setValue(Type _value);
  Type getValue(void);
};
#endif
