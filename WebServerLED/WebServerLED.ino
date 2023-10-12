#include <ESP8266WiFi.h>

const char *ssid = "DIT_CS_703";
const char *password = "";

#define RED_LED D1
int ledState = LOW;

WiFiServer server(80);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  //와이파이 접속
  WiFi.begin(ssid, password);
  //와이파이 접속 상태 확인하여 연결될 때까지 기다리기
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP : "); Serial.println(WiFi.localIP());
  //서버 구동 시작
  server.begin();
  Serial.println("HTTP Server started.");
}

void loop() {
  //클라이언트 접속 확인
  client = server.available();
  //클라이언트가 없으면 실행 종료
  if(!client) return;

  Serial.println("new client");
  while(!client.available()) { //클라이언트가 있다면 사용할 수 있을 때까지 기다림
    delay(1);
  }
  //request의 첫번째 줄인 요청라인을 읽어드림
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if(request.indexOf("LEDON") != -1) { //request로 전해진 데이터가 /LEDON 이면 불켜기
    digitalWrite(RED_LED, HIGH);
    ledState=HIGH;
  }
  if(request.indexOf("LEDOFF") != -1) {  //request로 전해진 데이터가 /LEDOFF 이면 불끄기
    digitalWrite(RED_LED, LOW);
    ledState=LOW;
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type text/html");
  client.println("");

  String aa = "<!DOCTYPE HTML><HTML><br>";
    aa += "Click <a href=\"LEDON\">here</a> RED LED ON<br>";
    aa += "Click <a href=\"LEDOFF\">here</a> RED LED OFF<br>";
    aa += "</HTML>";
  client.println(aa);

}
