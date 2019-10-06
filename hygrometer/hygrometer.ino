const int hygrometer = A0;  //Hygrometer sensor analog pin output at pin A0 of Arduino
const int pump = A2;
const int redPin = 4;
const int greenPin = 6;
const int bluePin = 7;

const int read_every_in_ms = 2000;

// Colours
const int off[] = {0,0,0};
const int red[] = {255,0,0};
const int blue[] = {0,0,255};
const int green[] = {0,255,0};
const int white[] = {255,255,255};
const int yellow[] = {255,255, 0};
const int orange[] = {140,20,50};
const int purple[] = {80,0,80};
const int aqua[] = {0,255,255};

#define COMMON_ANODE
  
//Variables 
int value;
int pumpState;

void setup(){
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT); 
  pumpState = 0;
  Serial.begin(9600);
}

void loop(){
  // When the plant is watered well the sensor will read a value 380~400, I will keep the 400 
  // value but if you want you can change it below. 
  int *color = off;
  pumpState = (pumpState + 1) % 2;
  analogWrite(pump, pumpState * 255); 
  value = analogRead(hygrometer);   //Read analog value 
  Serial.print("Raw: ");
  Serial.print(value);
  Serial.print("  ");
  value = constrain(value,0,200);  //Keep the ranges!
    Serial.print("Constrained: ");
  Serial.print(value);
  Serial.print("  ");
  value = map(value,0,200,100,0);  //Map value : 50 will be 100 and 500 will be 0
  if (value > 90) {
    setColor(white);
  } else if (value > 80) {
    setColor(aqua);
  } else if (value > 60) {
    setColor(blue);
  } else if (value > 50) {
    setColor(green);
  } else if (value > 40) {
    setColor(purple);
  } else if (value > 30) {
    setColor(yellow);
  } else if (value > 20) {
    setColor(orange);
  } else {
    setColor(red);
  }
  Serial.print("Soil humidity: ");
  Serial.print(value);
  Serial.println("");
  delay(read_every_in_ms);
}

void setColor(int color[])
{
  int red = color[0];
  int green = color[1];
  int blue = color[2];
  
  #ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
