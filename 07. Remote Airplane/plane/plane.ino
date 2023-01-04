#include <Servo.h>

const int upDownPin=13;                   //Servo
const int rightLeftPin=12;
Servo upDownServo;
Servo rightLeftServo;

const int motorPin=10;                    //motor

//variables
bool engineOn=false;
int number=0;
int rightLeft = 90, upDown = 90;

void setup() {
  upDownServo.attach(upDownPin);
  rightLeftServo.attach(rightLeftPin);
  upDownServo.write(90);
  rightLeftServo.write(90);

  pinMode(motorPin, OUTPUT);

  Serial.begin(9600);            //xbee
  Serial1.begin(11520);          //terminal
}

void loop() {

  while (Serial.available()==0){}

  //get command
  String command = Serial.readString();
  Serial1.println(command);

  if (!engineOn && command!="5"){            //can only press 5 when engine is off
    Serial1.println("plane is off!");
    command = "";
  }else
    number = command.toInt();
  
  func(number);

}

void func (int num){
  switch (num) {
    case 5:                                    //power
      engineOn = !engineOn;
      if (engineOn){
        analogWrite(motorPin, 255);            //255 is speed
      }else{
        analogWrite(motorPin, 0);
        rightLeft = 90;               
        upDown = 90;
        rightLeftServo.write(rightLeft);       //reset the servos
        upDownServo.write(upDown);
      }
      break;    
    case 2:                                    //move up
      if (upDown+5 <= 135){
        upDown = upDown+5;
      }
      upDownServo.write(upDown);
      delay(10);
      break;
    case 8:                                    //move down
      if (upDown-5 >= 45){
        upDown = upDown-5;
      }
      upDownServo.write(upDown);
      delay(10);
      break;
    case 6:                                    //move right
      if (rightLeft+5 <= 135){
        rightLeft = rightLeft+5;
      }
      rightLeftServo.write(rightLeft);
      delay(10);
      break;
    case 4:                                    //move left
      if (rightLeft-5 >= 45){
        rightLeft = rightLeft-5;
      }
      rightLeftServo.write(rightLeft);
      delay(10);
      break;
  }
}
