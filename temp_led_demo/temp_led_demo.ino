
// these are the pins attached to the lilypad 
const int tempPin  = A1; // analong pin attached to temperature sensor
const int redPin   =  9; 
const int bluePin  = 10; 
const int greenPin = 11; 

int cIndex; // color map index

// cmap.h contains the color map table
#include "cmap.h"

// A/D settings for reading temperature sensor
const int MAX_TEMP_BITS = 10;             // number of bits used to read temperature analog
const int MAX_TEMP_INT = 2^MAX_TEMP_BITS; // integer steps used to read temperature
const float MAX_TEMP_RANGE_VOLTS = 5.0;   // maximum voltage range of temperature

// this function adapted from this gist: https://gist.github.com/jamesotron/766994
// colors range from [0,255] == [off,full on]
void setColorRgb(unsigned int red, unsigned int green, unsigned int blue){
  analogWrite(redPin,red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue); 
}

float tempRead(){  
  // reads from the temperature sensor and returns the temperature is degree Centigrade
  //
  // sensor output at 0 deg C is 0.5 V. 
  // linear coefficient is 10 mV/dec C
  // Microchip  MCP 9700, SparkFun part number DEV-08777 
  return ((float) analogRead(tempPin)) * MAX_TEMP_RANGE_VOLTS / (float) MAX_TEMP_INT  * 0.01 + 0.5;   
}

void setup() {
  // put your setup code here, to run once:

  // set up led for output
  pinMode(redPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(greenPin,OUTPUT); 

  // initialize RGB LEDs to off
  setColorRgb(0,0,0);

  cIndex = 0; 
}

void loop() {
  // put your main code here, to run repeatedly:

  // read thermometer

  // set color
  // test color map by cycling through all colors
  setColorRgb(CMAP[cIndex][0],CMAP[cIndex][1],CMAP[cIndex][2]); 
  cIndex++; 
  if (cIndex > N_CMAP_LEVELS) cIndex = 0; 
}
