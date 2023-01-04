const int sensorPin = A3;

//vars
int waterSensorValue=0, value=0;

void setup() {
  pinMode(sensorPin, INPUT);

  Serial.begin(9600);
  Serial1.begin(11520);
}

void loop() {
  //read from water sensor
  waterSensorValue = analogRead(sensorPin);
  //map to 0 to 100
  value = map(waterSensorValue, 0, 1023, 0, 100);
    Serial1.println("water sensor value:   ");
    Serial1.println(value);
    Serial1.println();
    Serial.print('<'); 	//Starting symbol
    Serial.print(value);//Value from 0 to 100
    Serial.println('>');//Ending symbol

  delay(500);
}



