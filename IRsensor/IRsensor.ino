void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.print("Initializing...");
}

void loop() {
  Serial.print("\nTesting...\n");
  //-------IR
  Serial.println("Distance IR voltage:");
  int irval = analogRead(5);
  //zakres inta 64-600
  //zakres V 0.1-2.8
  Serial.println(irval);
  Serial.println((float)irval / 615) * 1024;
  Serial.println(irval * (5.0 / 1023.0));

  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
  
}
