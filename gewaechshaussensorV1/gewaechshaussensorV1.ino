#include <EEPROM.h>
#include <AccelStepper.h>
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
int pirPin = 2;

AccelStepper stepper(AccelStepper::FULL4WIRE, 8, 10, 9, 11);

int button = 3;   //attach a button to digital pin 3
int LED = 7;      //attach an LED to digital pin 7
int tempsensor = 0;
int lightsensor = 3;
int points = 0;
int brightness = 100;
int lastvalue = 0;
unsigned long startTime;
unsigned long currentTime;
const unsigned long period = 3000;
unsigned long startLight;
unsigned long currentLight;
const unsigned long lightPeriod = 10000;
float currentTempValue = 0;
int addr = 0;

void setup()
{
    pinMode(pirPin, INPUT);
    Serial.begin(9600);
    pinMode(tempsensor, INPUT);
    pinMode(button, INPUT);  //define button an INPUT device
    pinMode(LED, OUTPUT); 
    lcd.begin(16, 2);
    lcd.setRGB(0, 0, brightness);
    lcd.setCursor(0, 0); //define LED an OUTPUT device
    lcd.print("Temp.:");
    lcd.setCursor(10, 0);
    lcd.print("Light:");
    startTime = millis();
    startLight = millis();
    stepper.setMaxSpeed(2500);
    stepper.setSpeed(400);
    
    
}

void loop()
{   
    
    
    int value = analogRead(tempsensor);
    int buttonState = digitalRead(button); //read the status of the button
    
    int raw_light = analogRead(lightsensor); // read the raw value from light_sensor pin (A3)
    int light = map(raw_light, 0, 1023, 0, 100); // map the value from 0, 1023 to 0, 100
    
    currentTime = millis();
    currentLight = millis();
    currentTempValue = (value / 1.8 - 32) / 10;

    if (buttonState == 1){
      if (currentLight - startLight >= lightPeriod){
        lcd.setRGB(0, 0, 255);
        startLight = currentLight;
      }
      
    }
    else{
      lcd.setRGB(0, 0, 50);
    }
     
    if (currentTime - startTime >= period){
      
      lcd.setCursor(1, 1);
      lcd.print(currentTempValue);
      lcd.setCursor(11, 1);
      lcd.print(light);
      EEPROM.write(addr, currentTempValue);
      addr = addr + 1;
      if (addr == EEPROM.length()){
        addr = 0;
      }
      
      startTime = currentTime;
    }
    

    
    
    
    

    

    
    
    
    
      

    
    //if(buttonState == 1)
    //digitalWrite(LED,1);
    //else
    //digitalWrite(LED,0);
}