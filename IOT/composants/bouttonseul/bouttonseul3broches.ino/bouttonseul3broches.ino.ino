// Arduino and KY-004 module

void setup() {
  Serial.begin(9600);
  pinMode(18, INPUT_PULLUP); // KY-004 module is conected to pin 7
  pinMode(13, OUTPUT);      // built-in LED is connected to pin 13
}

void loop() {
  if (digitalRead(18) == LOW) {
    digitalWrite(13, HIGH);   // if button is pressed, turn on LED
  }
  else {
    digitalWrite(13, LOW); // if button is not pressed, turn off LED
  }

}