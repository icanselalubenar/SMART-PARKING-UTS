#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, -1);
const int trigPin[3] = {7, 5, 3};  
const int echoPin[3] = {6, 4, 2}; 
int slot;
float duration1, duration2, duration3;
float distance1, distance2, distance3;

void staticText() {
  display.setTextSize(2);
  display.setCursor(42, 0);
  display.println("SLOT");
  display.setCursor(30, 16);
  display.println("PARKIR");
}
void dynamicText() {
  display.setTextSize(4);
  display.setCursor(40, 34);
  display.println(slot);
}
void sensor1(){
  digitalWrite(trigPin[0], LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin[0], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin[0], LOW);
  duration1 = pulseIn(echoPin[0], HIGH);
  distance1 = (duration1*.0343)/2;
}
void sensor2(){
  digitalWrite(trigPin[1], LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin[1], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin[1], LOW);
  duration2 = pulseIn(echoPin[1], HIGH);
  distance2 = (duration2*.0343)/2;
}
void sensor3(){
  digitalWrite(trigPin[2], LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin[2], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin[2], LOW);
  duration3 = pulseIn(echoPin[2], HIGH);
  distance3 = (duration3*.0343)/2;
}

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  for(int i=0; i<3; i++) {
    pinMode(trigPin[i], OUTPUT);  
	  pinMode(echoPin[i], INPUT);  
  }
}

void loop() {
  sensor1();
  sensor2();
  sensor3();
  Serial.println(distance1);
  Serial.println(distance2);
  Serial.println(distance3);

  slot = 30;
  if(distance1 < 100) {
    slot = slot-1;
    if(distance2 < 100) {
      slot = slot-1;
      if(distance3 < 100) {
        slot = slot-1;
      }
    } else if(distance3 < 100) {
      slot = slot-1;
    }
  } else if(distance2 < 100) {
    slot = slot-1;
    if(distance3 < 100) {
      slot = slot-1;
    }
  } else if(distance3 < 100) {
    slot = slot-1;
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  staticText();
  dynamicText();
  display.display(); 

  delay(1000);
}