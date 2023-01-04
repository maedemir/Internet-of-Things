//buzzer
const int buzzerPin = 13;

//Variables
bool started= false;//Message is strated
bool ended 	= false;//Message is finished 
char incomingByte ; //store the incoming byte
char msg[3];		//Message
byte index;			//Index of array


void setup() {
  pinMode(buzzerPin, OUTPUT);

  //xbee
  Serial.begin(9600);
  //terminal
  Serial1.begin(11520);
}

void loop() {
 
  while (Serial.available()>0){
  	//Read the incoming byte
    incomingByte = Serial.read();
    //Start the message with '<' symbol
    if(incomingByte == '<'){
     started = true;
     index = 0;
     msg[index] = '\0'; // Throw away any incomplete packet
    }
    //End the message with '>' symbol
    else if(incomingByte == '>'){
      ended = true;
      break; // Message finished. exit from while
    }
    //Read the message!
    else{
      if(index < 4){ // Make sure array is not full
        msg[index] = incomingByte; // Add char to array
        index++;
        msg[index] = '\0'; // Add NULL to end
      }
    }
 }
 
  if(started && ended){
    int value = atoi(msg);

    //process
    Serial1.println("water sensor value:");
    Serial1.println(value);
    Serial1.println();
    if (value>95){
      Serial1.println("Water level is HIGH!");
      Serial1.println();
      digitalWrite(buzzerPin, OUTPUT);
      delay(500);
      digitalWrite(buzzerPin, INPUT);
    } else if (value<10){
      Serial1.println("Water level is LOW!");
      Serial1.println(); 
    } else {
      Serial1.println("Water level is NORMAL!");
      Serial1.println(); 
    }

    //reset the message
    index = 0;
    msg[index] = '\0';
    started = false;
    ended = false;
  }

}