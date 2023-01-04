#include <Servo.h>

Servo water;
Servo window;
int gas = 0;
int gas_value = 0;
int fire_value = 0;

void setup() {
  water.attach(13);
  window.attach(12);
  pinMode(10, INPUT);
  pinMode(9, INPUT);
  pinMode(11, OUTPUT);
  closeWater();
  closeWindow();
}

void loop() {
  fire_value = digitalRead(10);
  gas_value = digitalRead(9);
  
  if (fire_value == HIGH){
    openWater();
    digitalWrite(11,HIGH);
    delay(1000);
    digitalWrite(11,LOW);
    closeWater();
  }
  if (gas_value == HIGH && gas == 0){
    openWindow();
    digitalWrite(11,HIGH);
  }
  if (gas_value == LOW && gas == 1){
    closeWindow();
    digitalWrite(11,LOW);
  }
  delay(50);
}

void openWater (){
  for (int i = 0; i <= 180; i = i + 10) {
      water.write(i);
      delay(10);
    }
}

void closeWater (){
  for (int i = 180; i >= 0; i = i - 10) {
      water.write(i);
      delay(10);
    }  
}

void openWindow (){
  gas = 1;
  for (int i = 0; i <= 180; i = i + 10) {
      window.write(i);
      delay(10);
    }
}

void closeWindow (){
  gas = 0;
  for (int i = 180; i >= 0; i = i - 10) {
      window.write(i);
      delay(10);
    }  
}
