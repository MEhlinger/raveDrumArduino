#include <CapacitiveSensor.h>

// LED / Bare Paint CapSense DrumLight
// Marshall Ehlinger

/* Declarations and Initializations */
int ledPin1 = 9;
int ledPin2 = 11;
// Max and Min inputs calibrated for two 10Megaogm resistors in series
const long MAX_INPUT = 20000; //Approximate max from proximity sensing, not touch
const long MIN_INPUT = 650;
long input;

int debugCount;

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);
// 10Mohm resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired



/* Main Program Setup and Loop */
void setup()  
{ 
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  Serial.begin(9600);
  
  debugCount = 0;
}

void loop()
{
  input = getCapSensorInput();
  debugCount ++;
  
  if (debugCount % 50 == 0) //For serial debugging
  {
    Serial.println("  input: ");
    Serial.println(input);
    Serial.println("  brightness: ");
    Serial.println(convertToBrightness(input, MAX_INPUT));
  }
  
  if (input <= MIN_INPUT)
  {
    analogWrite(ledPin1, 0);
    analogWrite(ledPin2, 0);
  }
  
  else if (input <= MAX_INPUT) // For proximity sensing
  {
    analogWrite(ledPin1, convertToBrightness(input, MAX_INPUT));
    analogWrite(ledPin2, 0);
  }

  else
  {
    analogWrite (ledPin1, 255);
    analogWrite (ledPin2, 255);
  }
}



/* Functions */
int convertToBrightness(long input, long maxInput)
{
 int newBrightness = input * 255 / maxInput;
 return newBrightness;
}

long getCapSensorInput()
{
  long sensorValue = cs_4_2.capacitiveSensor(30);
  return sensorValue;
}
