#include<ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <Time.h>
#include <Hash.h>
#include <SocketIoClient.h>
#include <WiFiManager.h>
#include<ArduinoJson.h>
#include <DeviceData.h>
//===================================================================================
// DEFINES
//===================================================================================
#define HOST "10.7.227.77" // host de envio
#define PORT 3000 // porta para envio
#define GETDATAHORA "http://api.saiot.ect.ufrn.br/api/log/data-hora"

//===================================================================================
// VARIABLES
//===================================================================================

SocketIoClient socket;
WiFiManager wifi;
DeviceData device;

String ipStr;
String dataAtual;
char devStatus[400];

StaticJsonBuffer<400> jsonBuffer;

//===================================================================================
// FUNCTIONS
//===================================================================================
String getHoraAtual() {
  HTTPClient http;
  http.begin(GETDATAHORA);
  int httpCode = http.GET(); //Retorna o código http, caso não conecte irá retornar -1
  String payload = http.getString();
  http.end();
  if (httpCode != 200) {
    return "0";
  }
  return payload;
}

void setJson(DeviceData d){

  JsonObject& clientData = jsonBuffer.createObject();

  clientData["deviceId"] = device.getId();
  clientData["ip"] = device.getDeviceIp();
  clientData["tag"] = device.getTag();
  clientData["communicationType"] =device.getCommType();
  clientData["description"] = device.getDescription();
  clientData["timeout"] = device.getTimeout();
  clientData["state"] = device.getState();
  clientData["intensity"] = device.getIntensity();
  clientData["consumption"] = device.getConsumption();
  clientData["dateTime"] = device.getDateTime();
  clientData["actionAdress"] = device.getActionAdress();

  clientData.printTo(devStatus);
}

void sendStatus(const char * payload, size_t length){
   setJson(device);
  socket.emit("on_status", devStatus);
}

//===================================================================================
// SETUP
//=================================================================================

void setup(void) {

  Serial.begin(115200); // inicia o serial
  wifi.autoConnect(); // conectar no ultimo wifi salvo
  socket.begin(HOST, PORT); // inicia a conexão com o servidor

  IPAddress ip = WiFi.localIP();
  ipStr = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
  
  dataAtual = getHoraAtual();

//EXEMPLO
  device.setId("ESP001");
  device.setTag("LAMPADA_LAB");
  device.setDescription("Lampada que se encontra no lab 402(LII)");
  device.setDeviceIp(ipStr);
  device.setDateTime(dataAtual);
  device.setActionAdress("rota/postar/dados");
  device.setCommType(1); //1 - síncrona, 0 - assíncrona
  device.setState(1); //1 - ON, 0- OFF
  device.setTimeout(5);
  device.setIntensity(50.5);
  device.setConsumption(500.255);
  device.setDeadBand(0.3);

  socket.on("status", sendStatus);
  //socket.on("on",);
  //socket.on("off");
  //socket.on("configuration")

}

//===================================================================================
// LOOP
//===================================================================================

void loop() {
  socket.loop();
}
