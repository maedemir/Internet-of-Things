#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

const char keys[4][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'}, {'*','0','#'} };
const byte row_pins[4] = {22, 23, 24, 25};
const byte col_pins[3] = {26, 27, 28};
Keypad keypad = Keypad( makeKeymap(keys), row_pins, col_pins, 4, 3);
LiquidCrystal lcd(13, 12, 8, 9, 10, 11); // rs,en,d4,d5,d6,d7
Servo servo;

int p1 = 0; // 0-> free 1-> full
int p2 = 0; // 0-> free 1-> full
int p3 = 0; // 0-> free 1-> full
String id = "1";
String password = "2";
String input_string = ""; // keypad str
int state = 0; //0-> check id 1-> check pass 2-> ok
int column = 0;
int c1 = 0; // cost 1
int c2 = 0; // cost 2
int c3 = 0; // cost 3
int servo_state = 0;

void setup(){ 
    Serial.begin(9600);
    servo.attach(2);
    close();
    pinMode(51,OUTPUT);
    pinMode(52,OUTPUT);
    pinMode(53,OUTPUT);
    lcd.begin(16, 4);
    lcd.setCursor(0, 0);
    digitalWrite(51,HIGH);
    digitalWrite(52,HIGH);
    digitalWrite(53,HIGH);
}
void loop(){
    free(); //checks free parking spots and set leds respectively
    char key = keypad.getKey();
    if(key){      
      if (key == '0'){
          // check id and password
          lcd.clear();
          free();
          lcd.setCursor(0, 1);
          if (state == 0){
            if (input_string == id){
              state = 1; 
              lcd.print("ID is correct");
              delay(100);
              lcd.clear();
              free();
              input_string = "";
            }else{
              state = 0; 
              lcd.print("ID is wrong");
              delay(100);
              lcd.clear();
              free();
              input_string = "";
             }
          }
          if (state == 1 and input_string != ""){
            if (input_string == password){
                state = 2;
                lcd.clear();
                free();
                lcd.setCursor(0, 1);
                lcd.print("Pass is correct");
                delay(100);
                lcd.clear();
                free();
                input_string = "";
            }else{
                state = 1;
                lcd.clear();
                free();
                lcd.setCursor(0, 1);
                lcd.print("Pass is wrong");
                delay(100);
                lcd.clear();
                free();
                input_string = "";
            }
          }
      } 
      else if (key == '#'){
          lcd.clear();
          lcd.setCursor(0, 0);
          free();
          input_string = "";
          column = 0;
      }else if (key == '*'){
          lcd.clear();
          lcd.setCursor(0, 0);
          free();
          if (input_string == "1"){
            lcd.clear();
            lcd.setCursor(0, 0);
            free();
            lcd.setCursor(0, 1);
            lcd.print(c1);
          } else if(input_string == "2"){
            lcd.clear();
            lcd.setCursor(0, 0);
            free();
            lcd.setCursor(0, 1);
            lcd.print(c1);
          }else if(input_string == "2"){
            lcd.clear();
            lcd.setCursor(0, 0);
            free();
            lcd.setCursor(0, 1);
            lcd.print(c1);
          }else{
          input_string = "";
          lcd.clear();
            lcd.setCursor(0, 0);
            free();
            lcd.setCursor(0, 1);
            lcd.print("wrong number");
          }
      }
      else{
        input_string = input_string + key;
        column = column + 1;
        lcd.setCursor(column,  1);
        if (column < 16){
            lcd.print(key);  
        } 
      }
    }

    if (state == 2 && (p1 != 1 || p2 != 1 || p3 != 1) && servo_state == 0){
     servo_state = 1;
     open(); 
     delay(1000);
     close();
    }

    p1 = digitalRead(A0);
    p2 = digitalRead(A1);
    p3 = digitalRead(A2);
    if (p1 == 1){
      c1 = c1 + 1;
    }
    if (p2 == 1){
      c2 = c2 + 1;
    }
    if (p3 == 1){
      c3 = c3 + 1;
    }
    delay(50);
}

void free(){
  int count = 0;
  if (p1 == 0){
    count = count + 1;
    digitalWrite(51,HIGH);
  }else{
    digitalWrite(51,LOW);
  }
  if (p2 == 0){
    count = count + 1;
    digitalWrite(52,HIGH);
  }else{
    digitalWrite(52,LOW);
  }
  if (p3 == 0){
    count = count + 1;
    digitalWrite(53,HIGH);
  }else{
    digitalWrite(53,LOW);
  }
  lcd.setCursor(0, 0);
  lcd.print("Free: ");
  lcd.print(count);
}

void close (){
  for (int i = 180; i >= 0; i = i - 10) {
      servo.write(i);
      delay(10);
    }  
}
void open (){
  for (int i = 0; i <= 180; i = i + 10) {
      servo.write(i);
      delay(10);
    }
}
