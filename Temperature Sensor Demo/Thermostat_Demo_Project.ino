#include <math.h> //include library for log function
#include "VernierLib.h"

float rawCount; //create global variable for reading from A/D converter (0-1023)
float temperature; //create global variable for temperature in Celsius

//Average temperature calculation variables
float avgTemp = 0;
float totalTemp = 0;
unsigned int counter = 0;

//Pins
unsigned short LED_PIN = 13;

void setup() {
  Serial.begin(9600); //setup communication to display

  //Pin setup
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  counter++; 
  
  rawCount=analogRead(A2); //read one data value (0-1023)
  temperature=thermistor(rawCount); //calculate temperature
  Serial.print("Tmp: ");
  Serial.println(temperature,1); // display temperature to one decimal)

  //Turn on lamp if temp is above 30
  if(temperature > 30) {
    digitalWrite(LED_PIN, LOW);                      
  } else {
    digitalWrite(LED_PIN, HIGH);    
  }

  //Calculate and display avg temp
  totalTemp += temperature;
  avgTemp = totalTemp/counter;   

  Serial.print("Avg: ");
  Serial.println(avgTemp, 1);
  
  delay(500);  
}

//This function calculates temperature from raw count
float thermistor(int raw) {
  const float resistor=15000; //initialize value of fixed resistor in Vernier shield
  float resistance; //create local variable for resistance
  float temp; //create local variable for temperature

  resistance=log(resistor*raw/(1024-raw)); //calculate resistance
  temp = 1 / (0.00102119 + (0.000222468 * resistance) + (0.000000133342 * resistance * resistance * resistance)); //calculate temperature using the Steinhart-Hart equation
  temp = temp - 273.15; //Convert Kelvin to Celsius                      
  return temp; //return the temperature
}
