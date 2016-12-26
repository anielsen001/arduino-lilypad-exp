
#include <stdio.h>

// these are the pins attached to the lilypad 
// analog pin A1 was the default when the lilypad was attached
// after breaking apart, A1 is not available, so switch to A2
const int tempPin  = A2; // analong pin attached to temperature sensor
const int redPin   =  9; 
const int bluePin  = 10; 
const int greenPin = 11; 

int cIndex; // color map index

// min and max Temp range for color mapping
float tempMax = 100.0; 
float tempMin = 60.0; 

// cmap.h contains the color map table
#include "cmap.h"

// A/D settings for reading temperature sensor
//const int MAX_TEMP_BITS = 10;             // number of bits used to read temperature analog
const int MAX_TEMP_INT = 1024; // integer steps used to read temperature, 10 bit a/d
const float MAX_TEMP_RANGE_VOLTS = 3.7;   // maximum voltage range of temperature
//const float MAX_TEMP_RANGE_VOLTS = 5.0;   // maximum voltage range of temperature


// this function adapted from this gist: https://gist.github.com/jamesotron/766994
// colors range from [0,255] == [off,full on]
void setColorRgb(unsigned int red, unsigned int green, unsigned int blue){
  analogWrite(redPin,red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue); 
}

int tempReadInt()
{
  return analogRead(tempPin); 
  
}
    
float tempRead(){  
  // reads from the temperature sensor and returns the temperature is degree Centigrade
  //
  // sensor output at 0 deg C is 0.5 V. 
  // linear coefficient is 10 mV/dec C
  // Microchip  MCP 9700, SparkFun part number DEV-08777 
  return ( ((float) analogRead(tempPin)) * MAX_TEMP_RANGE_VOLTS / (float) MAX_TEMP_INT -0.5 ) / 0.01 *9/5+32 ;   
}

void setup() {
  // put your setup code here, to run once:

  // configure serial output
  Serial.begin(9600); 

  // set up led for output
  pinMode(redPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(greenPin,OUTPUT); 

  // set up to read temperature
  pinMode(tempPin,INPUT); 

  // initialize RGB LEDs to off
  setColorRgb(0,0,0);

  cIndex = 0; 
}

void loop() {
  // put your main code here, to run repeatedly:

  // read thermometer
  char tstr[20];
  int tempInt = tempReadInt();
  float temp = tempRead(); 
  //sprintf(tstr,"temp = %d \n",temp); 
  
  int tempBp = (int) temp; 
  int tempAp = (int)(temp*10.0) % 10; 
  sprintf(tstr,"temp = %d -> %d.%d C\n",tempInt,tempBp,tempAp); 
  Serial.print(tstr); 

  // set color

  // force to min and max scale
  if (temp < tempMin) temp = tempMin; 
  if (temp > tempMax) temp = tempMax;

  // choose which color index to use
  cIndex = (temp - tempMin)/(tempMax - tempMin) * N_CMAP_LEVELS; 
  
  // test color map by cycling through all colors
  setColorRgb(CMAP[cIndex][0],CMAP[cIndex][1],CMAP[cIndex][2]); 
  //cIndex++; 
  //if (cIndex > N_CMAP_LEVELS) cIndex = 0; 

  delay(100);
}
