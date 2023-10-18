int greenPin = D1;
int whitePin = D2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(whitePin,OUTPUT);
  pinMode(greenPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("hello, world");
  digitalWrite(whitePin, HIGH);
  digitalWrite(greenPin, LOW);
  delay(1000);
    digitalWrite(whitePin, LOW);
    digitalWrite(greenPin, HIGH);
  delay(1000);
   
}int greenPin = D1;
int whitePin = D2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(whitePin,OUTPUT);
  pinMode(greenPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("hello, world");
  digitalWrite(whitePin, HIGH);
  digitalWrite(greenPin, LOW);
  delay(1000);
    digitalWrite(whitePin, LOW);
    digitalWrite(greenPin, HIGH);
  delay(1000);
   
}
