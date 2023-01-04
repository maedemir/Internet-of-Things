#include <Keypad.h>

const byte ROWS = 4;                   //Keypad
const byte COLS = 3; 
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {50, 49, 48, 47}; 
byte colPins[COLS] = {53, 52, 51}; 
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

void setup() {
  Serial.begin(9600);                  //xbee
  Serial1.begin(11520);                //terminal
}

void loop() {
  //get key
  char key;
  key = myKeypad.getKey();
  if (key){                             //commands
    if (key=='5' || key=='6' || key=='4' || key=='8' || key=='2'){
      Serial.print(key);
      Serial1.println(key);
    }
  }

}
