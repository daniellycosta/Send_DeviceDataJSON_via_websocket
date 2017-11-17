#include <Arduino.h>
#include "DeviceData.h"

void DeviceData::setId(String _id){
  id = _id;
}
void DeviceData::setTag(String _tag){
  tag = _tag;
}
void DeviceData::setDescription(String _description){
  description =_description;
}
void DeviceData::setDeviceIp(String _deviceIp){
  deviceIp = _deviceIp;
}

void DeviceData::setActionAdress(String _actionAdress){
  actionAdress = _actionAdress;
}

void DeviceData::setCommType(bool _isSynchronous){
  isSynchronous = _isSynchronous;
}
void DeviceData::setState(bool _isOn){
  isOn = _isOn;
}

void DeviceData::setTimeout(int _timeout){
  timeout = _timeout;
}

void DeviceData::setDeadBand(float _deadBand){
  deadBand = _deadBand;
}

String DeviceData::getId(void){
  return id;
}
String DeviceData::getTag(void){
  return tag;
}
String DeviceData::getDescription(void){
  return description;
}
String DeviceData::getDeviceIp(void){
  return deviceIp;
}
String DeviceData::getDateTime(void){
  HTTPClient http;
  http.begin(F("http://api.saiot.ect.ufrn.br/v1/history/data-hora"));
  int httpCode = http.GET(); //Retorna o código http, caso não conecte irá retornar -1
  String payload = http.getString();
  http.end();
  if (httpCode != 200) {
    dateTime = "0";
  }
  dateTime = payload;
  return dateTime;
}
String DeviceData::getActionAdress(void){
  return actionAdress;
}
String DeviceData::getCommType(void){
  if(isSynchronous)
    return "synchronous";
  else
  return "asynchronous";
}
String DeviceData::getState(void){
  if(isOn)
    return "on";
  else
    return "off";
}

int DeviceData::getTimeout(void){
  return timeout;
}

float DeviceData::getDeadBand(void){
  return deadBand;
}
