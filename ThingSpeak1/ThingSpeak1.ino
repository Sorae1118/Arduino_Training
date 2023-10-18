#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

DHT dht (D1, DHT11);
WiFiClient client;

//LED 설정
#define LED D2

//WiFi 연결 정보
const char *ssid = "소래야";
const char *password ="10101010";

//ThingSpeak 연결 정보
unsigned long channel_id = 2305630; //unsigned 자료형은 c에서 절댓값을 의미함.
const char *api_key = "P0V5SINOCHDE1BUT";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //전송 속도
  WiFi.begin(ssid, password);
  dht.begin();
  pinMode(LED, OUTPUT);

  // WL_CONNECTED : WiFi 공유기에 성공적으로 연결이 된 후 
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP : "); Serial.println(WiFi.localIP());

  //ThingSpeak와 연결 시작
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if(isnan (temperature) || isnan (humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Temp : ");
  Serial.print(temperature);
  Serial.print("Humi : ");
  Serial.println(humidity);

  //채널의 속성 데이터와 연결
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);

  //ThingSpeak의 모든 필드에 데이터 기록
  int x = ThingSpeak.writeFields(channel_id, api_key);

  //기록이 잘 되었으면 응답이 200이고 OK(성공)
  if(x == 200) {
    Serial.println("Channel update successful.");
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
  }else {
    Serial.println("Problem updating channel. Http error code " + String(x));
  }

  //무료계정은 15초 이상이어야 함
  delay(15000);
}
