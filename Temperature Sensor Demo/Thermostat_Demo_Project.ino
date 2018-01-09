#include <math.h> //include library for log function

//Variables for temperature calculation
float rawCount; //create global variable for reading from A/D converter (0-1023)
float temperature; //create global variable for temperature in Celsius

//Average temperature calculation variables
float avgTemp = 0;
float totalTemp = 0;
unsigned int counter = 0;

//Pins are assigned here
unsigned short LED_PIN = 13;

void setup() {
  //Setup serial communication so results appear in the Serial Console
  Serial.begin(9600); 
  
  //Pin setup
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  counter++; //Increment counter for correct loop number 
  
  rawCount=analogRead(A2); //read one data value (0-1023)
  temperature=thermistor(rawCount); //calculate temperature
  
  //Turn on lamp if temp is above 30
  if(temperature > 30) {
    digitalWrite(LED_PIN, HIGH); //Set pin to high (on)                      
  } else {
    digitalWrite(LED_PIN, LOW);  //Set pin to low (off)  
  }

  //Calculate and display avg temp
  totalTemp += temperature;
  avgTemp = totalTemp / counter;

  //Print current temp
  Serial.print("Tmp: ");
  Serial.println(temperature,1);

  //Print average temp
  Serial.print("Avg: ");
  Serial.println(avgTemp, 1);

  //Delay for 0.5 seconds - we measure the temp twice each second
  delay(500);  
}

//The following function is made by some guys at MIT - not me
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
