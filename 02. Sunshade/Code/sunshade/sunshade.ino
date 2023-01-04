#include <Servo.h>
Servo servo;
const int water = A0;
const int ldr = A1;
int water_value = 0;
int light_value = 0;
int state = 0;
void setup() {
  servo.attach(9);
  close();
}

void loop() {
  light_value = analogRead(ldr);
  water_value = analogRead(water);
  if (water_value<500 && light_value<200 && state == 1) {
    close();
  }    
  if ((water_value>=500 || light_value>=200) && state == 0) {
    open();
  }  
  delay(50);  
}
void close (){
  state = 0;
  for (int i = 180; i >= 0; i = i - 10) {
      servo.write(i);
      delay(10);
    }  
}
void open (){
  state = 1;
  for (int i = 0; i <= 180; i = i + 10) {
      servo.write(i);
      delay(10);
    }
}
