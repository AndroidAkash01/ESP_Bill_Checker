#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "wifi_connect.h"
#include <time.h>
#include "time_utils.h"


#define NUM_LEDS 1
#define delay_time 40

#define RED_LIGHT 14
#define GREEN_LIGHT 15
#define BLUE_LIGHT 16

void turnOnLED(int pin, int brightness);
void turnOffLED(int pin);
void setColor(int r, int g, int b);
void redPulseTask(void *parameter);
void startredPulseTask();
void endredPulseTask();
void startbluePulseTask();
void endbluePulseTask();
void bluePulseTask(void *parameter);

 


float initialPrice = 0.0;
float currentPrice = 0.0;
bool redFlag = false;
 
void testPin(int pin) {
    Serial.print("Testing pin: ");
    Serial.println(pin);

    Adafruit_NeoPixel led(NUM_LEDS, pin, NEO_GRB + NEO_KHZ800);
    led.begin();
 
    // OFF
    led.clear();
    led.show();
    delay(400);
}

TaskHandle_t redPulseTaskHandle;
TaskHandle_t bluePulseTaskHandle;

bool isredPulseTaskRunning = false;
bool isbluePulseTaskRunning = false;

void setup() {
    Serial.begin(115200);
    delay(2000);
    pinMode(GREEN_LIGHT, OUTPUT);
    pinMode(RED_LIGHT, OUTPUT);
    pinMode(BLUE_LIGHT, OUTPUT);


    bool connection = connectToWiFi();
    initialPrice = getElectricityPrice();

    pinMode(GREEN_LIGHT, OUTPUT); 
    pinMode(RED_LIGHT, OUTPUT); 
    pinMode(BLUE_LIGHT, OUTPUT); 

    digitalWrite(GREEN_LIGHT, HIGH); // start OFF
    digitalWrite(RED_LIGHT, HIGH);
    digitalWrite(BLUE_LIGHT, HIGH); // start OFF
 
     // TEST ALL PINS
     startbluePulseTask();
  



    initTime();   // 👈 from time_utils






}
int x = 0;
void loop() {
    bool check_Connection = checkConnection();
    // testServer();
    turnOffLED(GREEN_LIGHT); 


    x++;
    float currentPrice = getElectricityPrice();

    if(initialPrice != currentPrice) {
      initialPrice = currentPrice;
      // turnOnLED(GREEN_LIGHT, 55); 
      // delay(2000);  
    }   
 

    //  currentPrice = 1.2;
    if(currentPrice > 0.41) {
      endbluePulseTask();
      startredPulseTask();
    }else{
      endredPulseTask(); 
      startbluePulseTask();
    }

 
    delay(120000);
}

void endredPulseTask() {
  if(isredPulseTaskRunning) {
    vTaskDelete(redPulseTaskHandle);
    isredPulseTaskRunning = false;
    turnOffLED(RED_LIGHT); // 💥 THIS is what turns LED ON

  }
}

void startredPulseTask() {
  if(!isredPulseTaskRunning) {
    isredPulseTaskRunning = true;
    xTaskCreate(
        redPulseTask,      // function
        "pulse Task",   // name
        5000,           // stack size
        NULL,
        3,
        &redPulseTaskHandle
    );
  }
}


void redPulseTask(void *parameter) {

 
    while (true) {

      for(int brightness = 0; brightness <= 255; brightness++) {
          analogWrite(RED_LIGHT, brightness); // 💥 THIS is what turns LED ON
          delay(1);
      }
      for(int brightness = 255; brightness >= 0; brightness--) {
          analogWrite(RED_LIGHT, brightness); // 💥 THIS is what turns LED ON
          delay(1);
      }

    }
}


// ################################ BLUE PULSE

void endbluePulseTask() {
  if(isbluePulseTaskRunning) {
    vTaskDelete(bluePulseTaskHandle);
    isbluePulseTaskRunning = false;
    turnOffLED(BLUE_LIGHT);  
  }
}

void startbluePulseTask() {
  if(!isbluePulseTaskRunning) {
    isbluePulseTaskRunning = true;
    xTaskCreate(
        bluePulseTask,      // function
        "pulse Task",   // name
        5000,           // stack size
        NULL,
        1,
        &bluePulseTaskHandle
    );
  }
}



void bluePulseTask(void *parameter) {

    int light = BLUE_LIGHT;
 
    while (true) {

      for(int brightness = 0; brightness <= 255; brightness++) {
          analogWrite(light, brightness); // 💥 THIS is what turns LED ON
          delayMicroseconds(10000);
      }
      for(int brightness = 255; brightness >= 0; brightness--) {
          analogWrite(light, brightness); // 💥 THIS is what turns LED ON
          delayMicroseconds(10000);
      }

    }
}

//#####################################




void turnOnLED(int pin, int brightness = 255) {
    Serial.print("Turning ON pin: ");
    Serial.println(pin);
    if(brightness < 0) {brightness = 0;}
    if(brightness > 255) {brightness = 255;}
    analogWrite(pin, 255 - brightness);  // 💥 THIS is what turns LED ON
}

void turnOffLED(int pin) {
    Serial.print("Turning OFF pin: ");
    Serial.println(pin);
    digitalWrite(pin, HIGH);   
    analogWrite(pin, 255);  // 💥 THIS is what turns LED OFF

}

 


// Helper: set full color
void setColor(int r, int g, int b) {
    turnOnLED(RED_LIGHT, r);
    turnOnLED(GREEN_LIGHT, g);
    turnOnLED(BLUE_LIGHT, b);
}


 


 // void turnOnLED(int pin) {

//     Adafruit_NeoPixel led(NUM_LEDS, pin, NEO_GRB + NEO_KHZ800);
//     led.begin();

//     led.setPixelColor(0, led.Color(255, 0, 0)); // RED
//     led.show(); // 💥 THIS actually sends data to LED

//     delay(800);
// }
