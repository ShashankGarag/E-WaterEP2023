#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Create LCD object
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Defining Variables
int trigPin = 3;
int echoPin = 4;
int waterDistance;
long testTime;
float duration;
float lastTimeUpdate;



//setup
void setup(){
  //initialize lcd
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  
  //Assign all pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  lastTimeUpdate = millis();

  //Print out prompts in Serial Monitor
  Serial.println("What Mode do you want?");
  Serial.println("Mode 1: Athletic");
  Serial.println("Mode 2: Study");
  Serial.println("Mode 3: Test");
  
}

//Function to take user input to select mode (time interval)
void messages(){
  int mode = Serial.parseInt();
  if(mode == 1){
    testTime = 20000;
  }
  if(mode == 2){
    testTime = 1000;
  }
  if(mode == 3){
    testTime = 5000;
  }
}

//Function that is running while device is on (loop)
void loop(){
  //Trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  //Measure return time and calculate distance
  duration = pulseIn(echoPin, HIGH);
  waterDistance = duration/58;

  //Make sure displayed water level is never negative
  if (waterDistance > 18){
    waterDistance = 18;
  }

  //Display the water level on the lcd
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("WL: " + String(18 - waterDistance) + " cm ");

  //Check for a decrease in water level after the time interval
  static int lastWaterLevel = 0;
  if(waterDistance > lastWaterLevel){
    //Display message on lcd
    lcd.setCursor(0,0);
    lcd.print("Keep it up!");
    lastTimeUpdate = millis();
  }
  lastWaterLevel = waterDistance;

  //Check if the water level has not changed over the time interval
  if(millis() - lastTimeUpdate > testTime){
    //Display message on lcd
    lcd.setCursor(0,0);
    lcd.print("Drink Water!");
    lastTimeUpdate = millis();
  }
 
  //Call the messages function
  messages();

  //Delay the time which the lcd screen updates (based on selected mode)
  delay(testTime);
}


 
 

