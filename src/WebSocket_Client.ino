#include <Arduino.h>

#include <ESP8266wifi.h>
#include<SocketIoClient.h>
#include<Hash.h>

 SocketIoClient client;


 const char* SSID = "LII";
 const char* password = "wifiLI2Rn";

#define host "10.7.227.77"
#define port 3000

 //char host[] = "10.7.227.77";
 //int port = 3000;

 char data[50];

void recebeu(String dados){
  Serial.print(dados);
}

void setup(){
  Serial.begin(115200);
  delay(10);

  //Conectando com wifi
  Serial.println("");
  Serial.println("");
  Serial.print("Conectando a ");
  Serial.println(SSID);

  WiFi.begin(SSID, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("");
  Serial.println("WIFI CONECTADO");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());

//Conectando com servidor

client.begin(host, port);
client.emit(data, "Hello World");
//
client.on("emit_test", recebeu);

}

void loop(){
  client.loop();
}
