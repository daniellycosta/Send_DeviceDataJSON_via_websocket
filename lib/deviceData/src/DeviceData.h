#ifndef DeviceData_h
#define DeviceData_h

#include <Arduino.h>

class DeviceData{
private:
  String id, tag, description,deviceIp,dateTime,actionAdress;
  bool isSynchronous, isOn;
  int timeout;
  double intensity, consumption, deadBand;

public:

  void setId(String _id);
  void setTag(String _tag);
  void setDescription(String _description);
  void setDeviceIp(String _deviceIp);
  void setActionAdress(String _actionAdress);

  void setCommType(bool _isSynchronous);
  void setState(bool _isOn);

  void setTimeout(int _timeout);

  void setIntensity(float _intensity);
  void setConsumption(float _consumption);
  void setDeadBand(float _deadBand);


  String getId(void);
  String getTag(void);
  String getDescription(void);
  String getDeviceIp(void);
  String getDateTime(void);
  String getActionAdress(void); //Action route
  //Will get the bool communication type (1-synchronous and 0-asynchronous) and
  //convert to a String
  String getCommType(void);
  //Will get the bool State (1-On and 0-Off) and convert to a String
  String getState(void);

  int getTimeout(void);

  float getIntensity(void);
  float getConsumption(void);
  float getDeadBand(void);
};

#endif
