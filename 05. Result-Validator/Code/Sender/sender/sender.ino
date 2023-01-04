#include <Keypad.h>
#include <SoftwareSerial.h>

SoftwareSerial terminal(2,3);
const char keys[4][4] = { 
  {'7','8','9', '/'},
  {'4','5','6', '*'},
  {'1','2','3', '-'},
  {'o','0','=', '+'} };
const byte row_pins[4] = {31, 33, 35, 37};
const byte col_pins[4] = {23, 25, 27, 29};
Keypad keypad = Keypad( makeKeymap(keys), row_pins, col_pins, 4, 4);
String data = "";

void setup(){
  Serial.begin(9600);
  terminal.begin (9600);
}

void loop (){
  char key = keypad.getKey();
  if(key){
    if (key == 'o'){
      Serial.println(data);
      data = "";
      terminal.println();
    }else{
      terminal.print(key);
      data = data + key;
    }
  }
}
