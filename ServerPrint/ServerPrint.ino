#include <ESP8266WiFi.h>

const char* ssid = "DIT_CS_703"; //사설 ip 사용
const char* password = "";

WiFiServer server(80);
WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("HTTP Server started");
}

void loop() {
  // put your main code here, to run repeatedly:료
  //클라이언트 접속 확인 
  client = server.available();
  //클라이언트가 없으면 실행 종료
  if(!client) return;

  //클라이언트가 있다면 사용할 수 있을 때까지 기다림
  Serial.println("new client");
  while(!client.available()) {
    delay(1);
  }
  //클라이언트의 request에 대한 response header를 클라이언트에 전송
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");

  String content = "<!DOCTYPE HTML><HTML><H2>Hi, Web Server!!</h2></HTML>";
  client.println(content);
  
}
