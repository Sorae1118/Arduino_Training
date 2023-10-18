#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHTPIN D4 
#define DHTTYPE DHT11 
#define ledPin D6

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.init(); // lcd init
  lcd.backlight(); // lcd back light on
  pinMode(ledPin, OUTPUT);
}
void loop() {
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" Humi: ");
  Serial.println(humi);

  // LCD Display
  // LCD Cursor change to (0,0)
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(char(223));
  lcd.print("C");
  
  // LCD Cursor change to (0,1)
  lcd.setCursor(0,1);
  lcd.print("Humi: ");
  lcd.print(humi);
  lcd.print("%");

  if (temp >= 28.0) {
    digitalWrite(ledPin, HIGH); // LED 켜기
  } else {
    digitalWrite(ledPin, LOW); // LED 끄기
  }
  
  delay(1000);
}
