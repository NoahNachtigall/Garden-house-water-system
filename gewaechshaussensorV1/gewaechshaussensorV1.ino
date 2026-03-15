#include <EEPROM.h>
#include <AccelStepper.h>
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
int pirPin = 2;

AccelStepper stepper(AccelStepper::FULL4WIRE, 8, 10, 9, 11);
int valveOpenSteps = 512;   // ~99° bei 200 Steps/Umdrehung
bool valveOpen = false;


int button = 3;   //attach a button to digital pin 3
int LED = 7;      //attach an LED to digital pin 7
int tempsensor = 0;
int lightsensor = 3;
int points = 0;
int brightness = 100;
int lastvalue = 0;
int potentiometer = 7;
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
    pinMode(button, INPUT_PULLUP);  //define button an INPUT device
    pinMode(LED, OUTPUT); 
    pinMode(potentiometer, INPUT);
    
    lcd.begin(16, 2);
    lcd.setRGB(255, 255, 255);
    lcd.setCursor(0, 0); //define LED an OUTPUT device
    lcd.print("Temp.:");
    lcd.setCursor(10, 0);
    lcd.print("Light:");
    startTime = millis();
    startLight = millis();
    stepper.setMaxSpeed(500);
    stepper.setAcceleration(200);
    
    
}

void loop()
{   
    
    
    int value = analogRead(tempsensor);
    int buttonState = digitalRead(button); //read the status of the button
    int raw_brightness = digitalRead(potentiometer);
    int brightness = (raw_brightness /4);
    
    int raw_light = analogRead(lightsensor); // read the raw value from light_sensor pin (A3)
    int light = map(raw_light, 0, 1023, 0, 100); // map the value from 0, 1023 to 0, 100
    
    currentTime = millis();
    currentLight = millis();
    currentTempValue = (value / 1.8 - 32) / 10;
    stepper.run();

    if (light <= 20){
      if (currentLight - startLight >= lightPeriod){
        lcd.setRGB(100, 100, 100);
        startLight = currentLight;
      }
    }
     else {
      lcd.setRGB(255, 255, 255);
    }
    
    
    if (digitalRead(button) == LOW) {   // Knopf gedrückt
    delay(200);                          // kleines Entprellen

    valveOpen = !valveOpen;              // Zustand wechseln

    if (valveOpen) {
      stepper.moveTo(valveOpenSteps);    // Ventil auf
    } else {
      stepper.moveTo(0);                 // Ventil zu
    }
    
    } 
     
    if (currentTime - startTime >= period){
      
      lcd.setCursor(1, 1);
      lcd.print(currentTempValue);
      lcd.setCursor(11, 1);
      lcd.print(light);
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("Temperture:");
      Serial.println(currentTempValue);
      Serial.println("----");
      Serial.println("Light:");
      Serial.println(light);
      Serial.println("----");
      if (valveOpen == true){
         Serial.println("Valve Open");
      }
      if (valveOpen == false){
        Serial.println("Valve Closed");
      }
      EEPROM.write(addr, currentTempValue);
      addr = addr + 1;
      if (addr == EEPROM.length()){
        addr = 0;
      }
      
      startTime = currentTime;
    }
    

    
   
}

//Days since Projectstart (08.03.2026)(free days inclusive):  8
//Finish Date: X

/*  ----Problems to fix:----
   - potentiometer to adjust brightness not working(idk why) 
   - eeprom memory fix(saved memory not readable)
   */

/*  ------IDEAS--------
    -data send to computer per wifi(concept in serial monitor)*/


