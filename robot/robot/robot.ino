#define irsensor0 A0
#define irsensor1 A1
#define irsensor2 A2
#define latency 1000
#include <Wire.h>
#define sonar 0x01
#define back 7
#define forward 6
#define left 5
#define right 4
#define power 9
#define radius 10

int dist_tab[] = {0,57125,29953,20515,15675,12717,10716,9269,8173,7312,6619,6047,5567,5159,4807,4500,4231,3992,3779,3587,3414,3257,3114,2983,2862,2750,2647,2552,2462,2379,2301,2228,2160,2095,2034,1977,1922,1871,1822,1775,1731,1688,1648,1610,1573,1537,1504,1471,1440,1410,1382,1354,1328,1302,1277,1253,1230,1208,1187,1166,1146,1126,1107,1089,1071,1054,1037,1021,1005,990,975,961,947,933,919,906,894,881,869,857,846,835,824,813,803,792,782,773,763,754,744,736,727,718,710,701,693,685,678,670,663,655,648,641,634,627,621,614,608,601,595,589,583,577,571,566,560,555,549,544,539,533,528,523,518,514,509,504,500,495,491,486,482,477,473,469,465,461,457,453,449,445,441,438,434,430,427,423,420,416,413,410,406,403,400,396,393,390,387,384,381,378,375,372,369,367,364,361,358,356,353,350,348,345,343,340,337,335,333,330,328,325,323,321,318,316,314,312,310,307,305,303,301,299,297,295,293,291,289,287,285,283,281,279,277,275,273,272,270,268,266,264,263,261,259,258,256,254,253,251,249,248,246,245,243,241,240,238,237,235,234,232,231,229,228,227,225,224,222,221,220,218,217,216,214,213,212,210,209,208,206,205,204,203,202,200,199,198,197,196,194,193,192,191,190,189,187,186,185,184,183,182,181,180,179,178,177,176,175,174,173,172,171,170,169,168,167,166,165,164,163,162,161,160,159,158,157,156,155,154,154,153,152,151,150,149,148,147,147,146,145,144,143,142,142,141,140,139,138,138,137,136,135,135,134,133,132,131,131,130,129,128,128,127,126,126,125,124,123,123,122,121,121,120,119,119,118,117,117,116,115,115,114,113,113,112,111,111,110,109,109,108,108,107,106,106,105,105,104,103,103,102,102,101,100,100,99,99,98,98,97,96,96,95,95,94,94,93,93,92,91,91,90,90,89,89,88,88,87,87,86,86,85,85,84,84,83,83,82,82,81,81,80,80,79,79,78,78,77,77,76,76,76,75,75,74,74,73,73,72,72,72,71,71,70,70,69,69,68,68,68,67,67,66,66,66,65,65,64,64,63,63,63,62,62,61,61,61,60,60,59,59,59,58,58,58,57,57,56,56,56,55,55,55,54,54,53,53,53,52,52,52,51,51,51,50,50,50,49,49,48,48,48,47,47,47,46,46,46,45,45,45,44,44,44,43,43,43,42,42,42,42,41};


void setup() {
  pinMode(back, OUTPUT);
  pinMode(forward, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(power, OUTPUT);
  pinMode(radius, OUTPUT);
  pinMode(13, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  //Serial.print("Initializing...");
      digitalWrite(back, LOW);
      digitalWrite(forward, LOW);
      digitalWrite(right, LOW);
      digitalWrite(left, LOW);
      analogWrite(radius, 220);
}

int irsensor(char num) {
  //Serial.println("Distance IR voltage:");
  int irval;
  if(num == 0)
    irval = analogRead(irsensor0);
  if(num == 1)
    irval = analogRead(irsensor1);
  if(num == 2)
    irval = analogRead(irsensor2);
  //zakres inta 64-600
  //zakres V 0.1-2.8
  //Serial.println(irval);
  //Serial.println("Distance:");
  if (irval<102 || irval>614) { // If voltage is lesser than 0.5 you cannot be sure if it's close or far; if greater than 3, there is something wrong
    //Serial.println("Out of range!");
    return -1;
  }
  else
  {
    int irdist = dist_tab[int(irval/2)];
    return int(irdist);
  } 
}


int sonarsensor() {
  byte a;
  byte b;
  Wire.beginTransmission(sonar);  //transmitting measure order
  Wire.write(0x10);
  Wire.write(0x02);
  Wire.endTransmission();
  delay(40);  //MUST WAIT BETWEEN TRANSMISSIONS
  Wire.beginTransmission(sonar);  //transmitting reply order
  Wire.write(0x20);
  Wire.endTransmission();
  delay(40);
  Wire.requestFrom(sonar, 2);
  a = Wire.read();
  b = Wire.read();
  int dist_val;
  dist_val = a+256*b;
  if (dist_val>3000)
    return -1;
  else
    return int(dist_val);
  
}

void loop() {
  
  int ir_back = irsensor(2);
  int ir_left = irsensor(1);
  int ir_right = irsensor(0);
  int sonar_forward = sonarsensor();
 

  Serial.print("\nTesting...\n");
  
  //-------sonar
  Serial.println("Distance Sonar:");
  if (sonar_forward == -1)
    Serial.println("Out of range!");
  else
    Serial.println(sonarsensor());
    
    
  //-------IR
  Serial.println("IR right -------------");
  if (ir_right == -1)
    Serial.println("Out of range!");
  else
    Serial.println(irsensor(0));  //cm
    
    
  Serial.println("IR left -------------");
  if (ir_left == -1)
    Serial.println("Out of range!");
  else
    Serial.println(irsensor(1));  //cm
    
    
  Serial.println("IR back -------------");
  if (ir_back == -1)
    Serial.println("Out of range!");
  else
    Serial.println(irsensor(2));  //cm
 
  
  //-------------LOGIC----------------------
  
  
      digitalWrite(left, LOW);
      digitalWrite(right, HIGH);
  if (ir_back < 1000 && ir_back > 10) {
    if (sonar_forward > 800)
    {
      //digitalWrite(back, LOW);
      //digitalWrite(forward, HIGH);
      digitalWrite(13, HIGH);
    }
    /* else if (ir_right > ir_left)
    {
      //digitalWrite(forward, LOW);
      //digitalWrite(back, HIGH);
      digitalWrite(right, LOW);
      digitalWrite(left, HIGH);
    } */
    else if (ir_right < ir_left)
    {
      //digitalWrite(forward, LOW);
      //digitalWrite(back, HIGH);
      //digitalWrite(left, LOW);
      //digitalWrite(right, HIGH);
      delay(500);
    }
    else
    {
      //digitalWrite(left, LOW);
      //digitalWrite(right, LOW);
      
    }
  }
  else {
    digitalWrite(forward, LOW);
    digitalWrite(back, LOW);
    digitalWrite(13, LOW);
  }
  //delay(latency);
  
}
