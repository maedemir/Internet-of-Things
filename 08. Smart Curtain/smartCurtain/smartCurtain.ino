#include <BlynkSimpleStream.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Template ID, Device Name and Auth Token
#define BLYNK_TEMPLATE_ID           "TMPLA2yOk0pd"
#define BLYNK_DEVICE_NAME           "blind"
#define BLYNK_AUTH_TOKEN            "q6fr-lQiJ_xqSOo5TbqQxGDrcggetHCj"

char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;

const int degreeServoPin=2;                      //servo
Servo degreeServo;

const int ldrPin=A15;                             //ldr

//vars
int mappedVal = 0, ldrVal = 0;
int userLightVal = 0;                     
int degreeVal = 0;



BLYNK_WRITE(V2){                    
  int pinValue = param.asInt();
  userLightVal = pinValue;
}

void myTimerEvent(){
  Blynk.virtualWrite(V1, mappedVal);
}

void setup() {
  degreeServo.attach(degreeServoPin);
  degreeServo.write(0);

  pinMode(ldrPin, INPUT);

  Serial1.begin(11520);                       //terminal

  Serial.begin(9600);                         //Blynk
  Blynk.begin(Serial, auth);

  timer.setInterval(1000L, myTimerEvent);
}

void loop (){
  //calculate outside light
  ldrVal = analogRead(ldrPin);
  mappedVal = map(ldrVal, 1, 683, 0, 100);
  Serial1.println("outside light:");
  Serial1.println(mappedVal);
  Serial1.println();

  //user given data
  Serial1.println("user given light value:");
  Serial1.println(userLightVal);
  Serial1.println();

  //calculate the needed degree of curtain
  if (mappedVal > userLightVal){
    int m = map((mappedVal-userLightVal), 0, 100, 0, 90);
    degreeVal = 90 - m;
    degreeServo.write(degreeVal);
  } else 
    degreeServo.write(90);
  
  Blynk.run();
  timer.run(); 

  delay(500);
}