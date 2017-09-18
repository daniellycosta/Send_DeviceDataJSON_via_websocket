#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>

#include <SocketIOClient.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <DeviceData.h>

//DEFINES
#define HOST "192.168.0.108" // host de envio
#define PORT 3001 // porta para envio
#define GETDATAHORA "http://api.saiot.ect.ufrn.br/v1/history/data-hora"

String getHoraAtual(void);
String setJson(DeviceData _device);
void sendStatus(String status);
void turnOn(String status);
void turnOff(String status);
void configuration(String status);

// VARIABLES
SocketIOClient socket;
WiFiManager wifi;
DeviceData device;

extern String RID;
extern String Rname;
extern String Rcontent;

String ipStr;
String dataAtual;

void setup() {
    Serial.begin(115200);
    Serial.flush();

    wifi.autoConnect();

    if (!socket.connect(HOST, PORT)) {
      Serial.println("connection failed");
      return;
    } else if (socket.connected()) {
      Serial.println("\n\n\n\n\nConectou no servidor\n\n\n");
    }

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
    socket.on("on", turnOn);
    socket.on("off", turnOff);
    socket.on("configuration", configuration);
}

void loop() {
    socket.monitor();
}

//FUNCTIONS
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

String setJson(DeviceData _device){

  String devStatus;
  //char devStatus[400];
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& clientData = jsonBuffer.createObject();

  clientData["deviceId"] = _device.getId();
  clientData["ip"] = _device.getDeviceIp();
  clientData["tag"] = _device.getTag();
  clientData["communicationType"] = _device.getCommType();
  clientData["description"] = _device.getDescription();
  clientData["timeout"] = _device.getTimeout();
  clientData["state"] = _device.getState();
  clientData["intensity"] = _device.getIntensity();
  clientData["consumption"] = _device.getConsumption();
  clientData["dateTime"] = _device.getDateTime();
  clientData["actionAdress"] = _device.getActionAdress();
  clientData["deadBand"] = _device.getDeadBand();

  clientData.printTo(devStatus);
  Serial.println(devStatus);
  return devStatus;
}

void sendStatus(String state){
  Serial.println();
  socket.emit("on_status", setJson(device));
  Serial.println("Enviou JSON!");
}
//funcoes On/Off - só alteram o estado se este estiver diferente
void turnOn(String status){
  if(device.getState() == "Off"){
  device.setState(1);
  socket.emit("on_status", setJson(device));
  Serial.println("Ligou!");
  }
}
void turnOff(String status){
  if(device.getState() =="On"){
  device.setState(0);
  socket.emit("on_status", setJson(device));
  Serial.println("Desligou!");
  }
}
void configuration(String status){
  //Criando Json para receber as conf. enviadas pelo server
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& newConfig = jsonBuffer.parseObject(status);
//testanto se o recebimento do json do server deu certo
  if (!newConfig.success()) {
    Serial.println("parseObject() failed");
    return;
  }
//setando novas configurações
  device.setTag(newConfig["tag"]);
  device.setDescription(newConfig["description"]);
  device.setTimeout(newConfig["timeout"]);
  device.setIntensity(newConfig["intensity"]);
  device.setDeadBand(newConfig["deadBand"]);
  if(newConfig["communicationType"] == "Synchronous")
    device.setCommType(1);
  else
    device.setCommType(0);
//enviando status atual
  socket.emit("on_status", setJson(device));
}
