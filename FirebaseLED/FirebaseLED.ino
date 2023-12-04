#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

const char *ssid = "DIT_CS_703";  
const char *password = "";     

//파이어베이스 API 키
#define FIREBASE_HOST "fir-led-control-c7013-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyByF0PKYKYXu9Hvlc7-uIteN6xzgtPQWWQ"

int led = D2;

//파이어베이스 데이터 객체 생성
FirebaseData fbdo;

String send_data = "OFF";
String read_data = "";

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
  Serial.println();
  delay(1000);

}

void loop() {
  if(Firebase.getString(fbdo, "LED_STATUS")) {
    read_data = fbdo.stringData();
    Serial.print("Read_data = ");
    Serial.println(read_data);

    if(read_data == "ON") {
      digitalWrite(led, HIGH);
      Serial.println("LED turned ON");
      
    }else if(read_data == "OFF") {
      digitalWrite(led, LOW);
      Serial.println("LED turned OFF");
      
    }
    Serial.println();
    
  }else {
    Serial.println(fbdo.errorReason());
  }
  
  delay(3000);

}
