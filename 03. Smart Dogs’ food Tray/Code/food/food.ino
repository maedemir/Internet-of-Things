#include <Servo.h>
#include <HX711.h>

Servo door;

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
HX711 scale;
int w = 0;

void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  door.attach(12);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(11, OUTPUT);
  closeDoor();
}

void loop() {
  w = scale.get_units()/1000;
  Serial.println(w);
  if (w >= 180){
    digitalWrite(11,LOW);
    digitalWrite(23,LOW);
    openDoor();
    digitalWrite(22,HIGH);
    delay(3000);
    closeDoor();
    digitalWrite(22,LOW);
  }
  if (w < 180){
    digitalWrite(11,HIGH);
    digitalWrite(23,HIGH);
  }  
  delay(6000);
}

void openDoor (){
  for (int i = 0; i <= 180; i = i + 10) {
      door.write(i);
      delay(10);
    }
}

void closeDoor (){
  for (int i = 180; i >= 0; i = i - 10) {
      door.write(i);
      delay(10);
    }  
}
