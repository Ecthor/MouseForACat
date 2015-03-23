#include <Wire.h>
#define sonar 0x01
#define reset 8

void initialize_sonar(){
  Wire.beginTransmission(sonar);  
  Wire.write(0x30);
  Wire.endTransmission();
}

void distance(byte *a, byte *b){
  Wire.beginTransmission(sonar);  
  Wire.write(0x10); 
  Wire.write(0x02);
  Wire.endTransmission();
  delay(500);
  Wire.beginTransmission(sonar);  
  Wire.write(0x20);
  Wire.endTransmission();
  Wire.requestFrom(sonar, 2);
  *a = Wire.read();
  *b = Wire.read();
}

byte testing(){
  Wire.beginTransmission(sonar);  
  Wire.write(0x40);
  Wire.endTransmission();
  Wire.requestFrom(sonar, 1);
  char a;
  a = Wire.read();
  return a;
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(reset, OUTPUT);
  digitalWrite(13, HIGH);
  digitalWrite(reset, HIGH);
  Wire.begin();
  Serial.begin(9600);
  Serial.print("Initializing...");
  //initialize_sonar();
  digitalWrite(13, LOW);
  //pinMode(A5, INPUT);
}

void loop() {
  Serial.print("\nTesting...\n");
  digitalWrite(13, HIGH);
  byte a;
  byte b;

  Serial.println("Distance Sonar:");
  distance(&a, &b);
  int dist_val;
  dist_val = a+256*b;
  Serial.println(dist_val);
  Serial.println(int(&a), BIN);
  Serial.println(int(&b), BIN);
  
  
  Serial.println("Sonar test:");
  Serial.println(testing(), BIN);

  //-------IR
  Serial.println("Distance IR voltage:");
  int irval = analogRead(5);
  Serial.println(irval * (5.0 / 1023.0));

  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
  
}
  
