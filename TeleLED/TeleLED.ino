#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>

const char *ssid = "DIT_CS_703";  
const char *password = "";  

#define BOT_TOKEN "6451399833:AAG2nJ01i2xw5IDC8Sv1a0hnlbxsa-fZTic"
#define CHAT_ID "6858765176"

int redPin = D2;
int greenPin = D3;
int yellowPin = D4;

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

void christmas() {
  digitalWrite(redPin, HIGH);
  delay(1000);
  digitalWrite(greenPin, HIGH);
  delay(1000);
  digitalWrite(yellowPin, HIGH);
  delay(3000);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  delay(1000);
  for(int i = 0; i < 5; i++) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(yellowPin, HIGH);
    delay(500);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, LOW);
    delay(500);
  }
}
void setup() {
  Serial.begin(115200);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);

  configTime(0, 0, "pool.ntp.org");

  secured_client.setTrustAnchors(&cert);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP :"); Serial.println(WiFi.localIP());
  
}

void loop() {
  int numNewMsg = bot.getUpdates(bot.last_message_received + 1);

  for(int i=0; i<numNewMsg; i++) {
    //전송된 메세지ㅇ서 chat_id 알아내기
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    Serial.println(text);
    Serial.println(chat_id);

    if (text == "red on") {
      digitalWrite(redPin, HIGH);
      bot.sendMessage(chat_id, "Red LED turned On");
    }
    if (text == "red off") {
      digitalWrite(redPin, LOW);
      bot.sendMessage(chat_id, "Red LED turned Off");
    }
    if (text == "green on") {
      digitalWrite(greenPin, HIGH);
      bot.sendMessage(chat_id, "Green LED turned On");
    }
    if (text == "green off") {
      digitalWrite(greenPin, LOW);
      bot.sendMessage(chat_id, "Green LED turned Off");
    }
    if (text == "yellow on") {
      digitalWrite(yellowPin, HIGH);
      bot.sendMessage(chat_id, "Yellow LED turned On");
    }
    if (text == "yellow off") {
      digitalWrite(yellowPin, LOW);
      bot.sendMessage(chat_id, "Yellow LED turned Off");
    }
    if (text == "all on") {
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, HIGH);
      digitalWrite(yellowPin, HIGH);
      bot.sendMessage(chat_id, "All LED turned On");
    }
    if (text == "all off") {
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(yellowPin, LOW);
      bot.sendMessage(chat_id, "All LED turned Off");
    }
    if (text == "christmas") {
      christmas();
      bot.sendMessage(chat_id, "Merry Christmas!");
    } else {
      bot.sendMessage(chat_id, "Wrong Command!");
    }
  }
}
