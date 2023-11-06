#include "Ubidots.h"
#include <DHT.h>

#define DHTPin D1
#define DHTType DHT11
#define LEDPin D2

DHT dht(DHTPin, DHTType);

const char* UBIDOTS_TOKEN = "BBUS-bH9cxPVC1bovL3eAd34w8AQvVlLJCx";
const char* WIFI_SSID = "DIT_CS_703";  
const char* WIFI_PASS = "";   

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

void setup() {

  Serial.begin(115200);
  dht.begin();
  pinMode(LEDPin, OUTPUT);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  // ubidots.setDebug(true);  // 디버그 메시지를 인쇄하려면 이 줄의 주석 처리를 제거하세요.
}

void loop() {

  float temp = dht.readTemperature();
  float humi = dht.readHumidity();

  int value = ubidots.get("a4cf12c5cca8","led");

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" Humi: ");
  Serial.println(humi);

  ubidots.add("Temperature", temp);
  ubidots.add("Humidity", humi);

  bool bufferSent = false;
  bufferSent = ubidots.send(); //장치 ID와 일치하는 장치 레이블로 데이터를 보냅니다.

  if (bufferSent) {
    // 값이 제대로 전송된 경우 조치를 취하세요.
    Serial.println("Values sent by the device");
  }
  
  if (value != ERROR_VALUE) { 
    Serial.print("Value:"); 
    Serial.println(value); 
  }

  if(value == 1) {
    Serial.println("LED On");
    digitalWrite(LEDPin, HIGH);
  } else if(value == 0) {
    Serial.println("LED Off");
    digitalWrite(LEDPin, LOW);
  }
  
  delay(5000);
}
