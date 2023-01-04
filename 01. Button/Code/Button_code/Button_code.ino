int ldr=A0;
int ldr_value=0;
bool state = false;
bool preState = true;

void setup() {
pinMode(22,OUTPUT);//led
}

void loop() {
 ldr_value=analogRead(ldr);
 if (cur_value < 250){
    if(!state && state!=preState){
      state = true;
      preState = state;
      digitalWrite(22,HIGH);
    }
    else if (state && state!=preState){
      state = false;
      preState = state;
      digitalWrite(22,LOW);
  }
} 
 else if (ldr_value >= 250){
    preState = !state;
  }
}
