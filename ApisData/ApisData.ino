#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
const char *ssid = "DIT_CS_703";
const char *password = "";

const String url = "https://apis.data.go.kr/B552584/ArpltnInforInqireSvc/getCtprvnRltmMesureDnsty?serviceKey=1ugI7jIkIEUURQM%2FcgliRW0FXNuNTHFewWd9uepXhoiGtbabh6LDPCWq846IEeTy5th0tW0uBUcq%2Bhn3yqNUpw%3D%3D&returnType=xml&numOfRows=1&pageNo=5&sidoName=%EB%B6%80%EC%82%B0&ver=1.0";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  lcd.init();
  lcd.backlight();

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP :"); Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();
    client.connect(url, 443);

    HTTPClient https;
    https.begin(client, url);

    int httpCode = https.GET();

    if(httpCode>0) {
      String result = https.getString();
      Serial.println(result);

      int pm10_1 = result.indexOf("<pm10Value>");
      int pm10_2 = result.indexOf("</pm10Value>");
      String pm10 = "<pm10Value>";

      String content = result.substring(pm10_1 + pm10.length(), pm10_2);
      Serial.println(content);
        
      //lcd
      lcd.setCursor(0, 0);
      lcd.print("PM10 : ");
      lcd.setCursor(7, 0);
      lcd.print(content);
    }
    https.end();
  }
  delay(60000);
}
