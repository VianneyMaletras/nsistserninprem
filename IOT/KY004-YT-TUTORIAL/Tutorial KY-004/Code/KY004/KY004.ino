//////////////////////////
// KY-004 Tutorial code //
//////////////////////////
int Led = 13;    // declearation of the LED output pin
int Sensor = 18;  // decleartion of the sensor input pin
int val;         // temporary variable

void setup() {
  pinMode(Led, OUTPUT);        // initialize output pin
  pinMode(Sensor, INPUT);       // initialize sensor pin
  digitalWrite(Sensor, HIGH);  // activate internal pull-up resistor
}

void loop() {
  val = digitalRead(Sensor);  // the current signal at the sensor is read out

  if (val == HIGH) {  // if a signal could be detected, the LED is switched on
    digitalWrite(Led, LOW);
  } else {
    digitalWrite(Led, HIGH);
  }
}