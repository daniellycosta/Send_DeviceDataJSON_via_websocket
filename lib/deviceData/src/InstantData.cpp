#include <Arduino.h>
#include "InstantData.h"

template <class Type> void InstantData<Type>::setValue(Type _value){
  value = _value;
}

template <class Type> Type InstantData<Type>::getValue(void){
  return value;
}
