
//Create a handle for the LED pin number
unsigned short LED_PIN = 13;

//Setup function, here we prepare the LED
void setup() {
  
  //Set pinmode of LED so we can to output it
  pinMode(LED_PIN, OUTPUT);
  
}

//The main function - this will loop
void loop() {
  
  //Turn on LED
  digitalWrite(LED_PIN, HIGH);

  //Pause program for 0.5 seconds, so the LED is on for half a second
  delay(500); 

  //Turn off LED
  digitalWrite(LED_PIN, LOW);

  //Pause program for 0.5 seconds, so the LED is off for half a second
  delay(500);
  
}
