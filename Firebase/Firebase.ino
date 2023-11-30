#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>


const char *ssid = "DIT_CS_703";  
const char *password = "";     

//파이어베이스 API 키
#define FIREBASE_HOST "fir-led-control-c7013-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyByF0PKYKYXu9Hvlc7-uIteN6xzgtPQWWQ"

//파이어베이스 데이터 객체 생성
FirebaseData fbdo;

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
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }


void loop() {
  if(Serial.available()) {
    //시리얼모니터에 line ending 없음을 선택한 뒤 실행할 것
    String greeting = Serial.readStringUntil('\r');

    //시리얼모니터에 입력한 내용을 파이어베이스에 입력하기
    bool res = Firebase.setString(fbdo, "/GREETING", greeting);
    if(res) {
      Serial.println("Set string...ok");
    } else {
      Serial.println(fbdo.errorReason().c_str());
    }
  }

}
