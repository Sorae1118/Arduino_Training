#include <ESP8266WiFi.h>
#include <DHT.h>

const char *ssid = "DIT_CS_703";
const char *password = "";

WiFiServer server(80); //서버 만들기
WiFiClient client;      
DHT dht(D4, DHT11);

void setup() {
  Serial.begin(115200);
  //와이파이 접속
  WiFi.begin(ssid, password);
  //와이파이 접속 상태 확인
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP :"); Serial.println(WiFi.localIP());
  //서버 구동 시작
  server.begin();
  Serial.println("HTTP Server started.");
  dht.begin();
}

void loop() {
  //클라이언트 접속 확인
  client = server.available();
  //클라이언트가 없으면 실행 종료
  if(!client) return;

  //클라이언트가 있다면 사용할 수 있을 때까지 기다림
  Serial.println("new client");
  while(!client.available()) { //사용 가능한 상태인지 확인
    delay(1);
  }
  //온습도 읽기
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();

  //클라이언트의 request에 대한 response header를 클라이언트에 전송
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");

  String content = "<!DOCTYPE HTML><HTML><h2>[Weather Station]</h2>";
    content += "<h3 style=\"background-color:pink\">Temperature : ";
    content += temp;
    content += "C</h3>";
    content += "<h3 style=\"background-color:lightblue\">Humidity : ";
    content += humid;
    content += "%</h3><br>";
  client.println(content);
}
