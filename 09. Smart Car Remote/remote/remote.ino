#include <BlynkSimpleStream.h>
#include <SoftwareSerial.h>
#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define BLYNK_TEMPLATE_ID "TMPL79WCZliY"
#define BLYNK_DEVICE_NAME "remote"
#define BLYNK_AUTH_TOKEN "fWWxJ-c2rsCmFcwhxbfx7YJdUC-DLb6O"

char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;

const byte ROWS = 4;                                                    //keypad
const byte COLS = 3; 
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {25, 26, 27, 28}; 
byte colPins[COLS] = {22, 23, 24}; 
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

const int servoPin = 5;                                                   //servo
Servo door;

const int blynkSystem = 3;                                                //led
const int blynkLights = 4;
const int carLight = 33;

const int buzzer = 6;                                                      //buzzer

const int ldr = A0;                                                        //ldr

const int sensor = A13;                                                    //water sensor

//variables
int ldrVal=0, outLight=0;                                                 //outside light
int waterSensorVal=0, waterVal=0;                                         //
int carLightVal=0, currentCarLight=0;                                     //given and current car light value
bool systemOn=false, lightOn=false;

BLYNK_WRITE(V1){
  int pinValue = param.asInt(); 
  carLightVal = pinValue;
}

BLYNK_WRITE(V0){
  bool pinValue = (param.asInt()==1)?true:false; 
  lightOn = pinValue;
  if (lightOn){
    digitalWrite(blynkLights, HIGH);
    digitalWrite(carLight, HIGH);
  }else{
    digitalWrite(blynkLights, LOW);
    digitalWrite(carLight, LOW);
    currentCarLight = 0;
  }
}

BLYNK_WRITE(V3){
  bool pinValue = (param.asInt()==1)?true:false; 
  systemOn = pinValue;
  if (systemOn)
    digitalWrite(blynkSystem, HIGH);
  else
    digitalWrite(blynkSystem, LOW);
}

void myTimerEvent(){
  Blynk.virtualWrite(V2, waterVal);
}

void setup() {
  Serial.begin(9600);                          //blynk
  Blynk.begin(Serial, auth);
  timer.setInterval(1000L, myTimerEvent);

  Serial3.begin(11520);                        //virtual terminal

  door.attach(servoPin);
  door.write(0);

  pinMode(sensor, INPUT);
  pinMode(ldr, INPUT);                        
  pinMode(buzzer, OUTPUT);
  pinMode(blynkSystem, OUTPUT);
  pinMode(blynkLights, OUTPUT);
  pinMode(carLight, OUTPUT);
}

void loop() {
  ldrVal = analogRead(ldr);
  outLight = map(ldrVal, 1, 683, 0, 100);

  if (outLight > 70){
    digitalWrite(carLight, LOW);
    currentCarLight = 0;
  } else {
    if (lightOn){
      digitalWrite(carLight, HIGH);
      currentCarLight = carLightVal;
    }
  }

  waterSensorVal = analogRead(sensor);
  waterVal = map(waterSensorVal, 0, 1020, 0, 100);

  serialPrint();

  char key;
  key = myKeypad.getKey();
  if(key){                 
    if(key == '*'){                      //open door
      if (systemOn){
        digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
      } else {
        door.write(90);
      }
    }
    if (key == '#'){                      //close door
      door.write(0);
    }
  }

  Blynk.run();
  timer.run(); 

  delay(400);
}

void serialPrint (){
  Serial3.print("outside light is->    ");
  Serial3.println(outLight);
  Serial3.println();
  Serial3.print("given car light is->    ");
  Serial3.println(carLightVal);
  Serial3.println();
  Serial3.print("current car light value is->    ");
  Serial3.println(currentCarLight);
  Serial3.println();
  Serial3.print("water value is->    ");
  Serial3.println(waterVal);
  Serial3.println();
}