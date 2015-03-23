#include <Wire.h>
#define sonar 0x01
#define reset 8


void setup() {
  pinMode(13, OUTPUT);
  pinMode(reset, OUTPUT);
  digitalWrite(13, HIGH);
  digitalWrite(reset, HIGH);
  Wire.begin();
  Serial.begin(9600);
  Serial.print("Initializing...");
  digitalWrite(13, LOW);
}

void loop() {
  Serial.print("\nTesting...\n");
  digitalWrite(13, HIGH);
  byte a;
  byte b;
  
  Wire.beginTransmission(sonar);  //transmitting measure order
  Wire.write(0x10); 
  Wire.write(0x02);
  Wire.endTransmission();
  delay(50);  //MUST WAIT BETWEEN TRANSMISSIONS
  Wire.beginTransmission(sonar);  //transmitting reply order
  Wire.write(0x20);
  Wire.endTransmission();
  delay(50);
  Wire.requestFrom(sonar, 2);
  a = Wire.read();
  b = Wire.read();
  Serial.println("Distance Sonar:");
  int dist_val;
  dist_val = a+256*b;
  //Serial.println(int(a), BIN);
  //Serial.println(int(b), BIN);
  if (dist_val>3000)
    Serial.println("Out of range!");
  else
    Serial.println(float(dist_val)/10.0);
  
  
  Serial.println("Sonar test:");
  
  Wire.beginTransmission(sonar);  //transmitting test order, should reply with 123
  Wire.write(0x40);
  Wire.endTransmission();
  delay(50);
  Wire.requestFrom(sonar, 1);
  char m;
  m = Wire.read();
  Serial.println(int(m));
  
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  
}
  
