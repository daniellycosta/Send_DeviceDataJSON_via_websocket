#include <Arduino.h>

#include <ESP8266wifi.h>
#include<SocketIOClient.h>

 SocketIOClient client;


 const char* SSID = "LII";
 const char* password = "WifiLI2Rn";

 char host[] = "10.7.227.70";
 int port = 3000;
 char data[50];

void setup(){
  Serial.begin(115200);
  Serial.println("Pronto!");
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

if (!client.connect(host, port)){
  Serial.println("falha na coneccao com o servidor");
}

if(client.connected()){
  Serial.println("CONECTADO COM O SERVIDOR");
  //client.emit(data,"Connected !!!!");
}

}

void loop(){
    //data = Serial.read();
    //client.emit();
    delay(500);
}
