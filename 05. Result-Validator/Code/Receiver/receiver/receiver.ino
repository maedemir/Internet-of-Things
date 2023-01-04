#include <SoftwareSerial.h>

SoftwareSerial terminal(2,3);
String data;
int result = 0;

void setup() {
  Serial.begin (9600);
  terminal.begin (9600);
  pinMode(22,OUTPUT); // Green LED
  pinMode(23,OUTPUT); // Red LED
}

void loop() {
  if (Serial.available()){
      data = Serial.readString();
      terminal.println("Input: " + data);
      if (calculate(data) == 0){
        terminal.print("Wrong! Result: ");
        terminal.println(result);
        digitalWrite(23,HIGH);
        delay(3000);
        digitalWrite(23,LOW);
      }else{
        terminal.println("Correct Answer!");
        digitalWrite(22,HIGH);
        delay(3000);
        digitalWrite(22,LOW);
      }
    }
}

int value(char c) {  
  return (c - '0'); 
}

int find_result_in_exp(String s){
  int temp = 0;
  int flag = 0;
  
  for (int i = 1; i < s.length() ; i = i + 1){
    if (flag == 1 && s[i] >='0' && s[i] <='9'){
      temp = temp*10 + value(s[i]);
    }
    if (s[i] == '='){
      flag = 1; 
    }
  }
  return temp;
}

int calculate(String str){
  int res = value(str[0]);
   for (int i = 1 ; i < str.length() ; i = i + 2){
    if (str[i] == '='){
      break;
    }
    char op = str[i];
    char var = str[i+1];
    if (op == '+'){
      res = res + value(var);
    }
    else if (op == '-'){
      res = res - value(var);
    }
    else if (op == '*'){
      res = res * value(var);
    }
    else if (op == '/'){
      res = res / value(var);   
    }
   }
   result = res;
   if (res == find_result_in_exp(str)){
    return 1;
   }
   return 0;
}
