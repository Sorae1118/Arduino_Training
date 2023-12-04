#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>

const char *ssid = "DIT_CS_703";  
const char *password = "";     

//파이어베이스 API 키
#define FIREBASE_HOST "fir-led-control-c7013-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyByF0PKYKYXu9Hvlc7-uIteN6xzgtPQWWQ"

//파이어베이스 데이터 객체 생성
FirebaseData fbdo;

DHT dht(D1, DHT11);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP : ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //파이어베이스 연결
  Firebase.reconnectWiFi(true);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //온습도 센서 시작
  Serial.println("DHT11 test!");
  dht.begin();
}

int n = 0;

void loop() {
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();

  //측정값이 없을 경우 return
  if (isnan(temp) || isnan(humi)) {
    Serial.print("Error");
    return;
  }
  n++;  //입력 개수 카운터
  Firebase.pushInt(fbdo, "/nodeMCU/num", n);
  Firebase.pushFloat(fbdo, "/nodeMCU/Temperature", temp);
  Firebase.pushFloat(fbdo, "/nodeMCU/Humidity", humi);
  
  delay(5000);
}
