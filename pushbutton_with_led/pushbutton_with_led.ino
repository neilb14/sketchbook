const int ledPin = A1;
const int buttonPin = 2 ;     // the number of the pushbutton pin
const int timeoutMins = 6 * 60;
const unsigned long timeout = (unsigned long) timeoutMins * 60 * 1000;
const int ledOn = 255;
const int ledOff = 0;

// variables will change:
unsigned long onAt = 0;
int buttonState = 0;
int ledValue = ledOn;

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Serial.println("Starting");
}

void loop() {
  analogWrite(ledPin, ledValue);
  unsigned long currentTime = millis();
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
      ledValue = ledOff;
      onAt = currentTime;
      analogWrite(ledPin, ledValue);
  }
  if (currentTime%5000 == 0) {
    Serial.print("Time is: ");
    Serial.print(currentTime);
    Serial.print(" timeoutAt: ");
    Serial.print(onAt+ timeout);
    Serial.println();
  }
  if ((onAt > 0) && ((onAt + timeout) <= currentTime)) {
    onAt = 0;
    ledValue = ledOn;
    analogWrite(ledPin, ledValue);
  }
}
