#include <ESP8266WiFi.h>
#include <Wire.h>
#include <String>
#include <SPI.h>
#include "rgb_lcd.h"
#include "SparkFunLSM6DS3.h"
#include "math.h"

// compile time constants
#define PAYLOADSIZE 5
#define LCD_ADDRESS 0x3c
#define ACC_ADDRESS 0x6b
#define ARD_ADDRESS 0x09
#define MST (-7)
#define UTC (0)
#define CCT (+8)

// initialize LSM data
LSM6DS3 myIMU;
float LSMData = 0;
unsigned long curr_LSM_timer = 0;
unsigned long prev_LSM_timer = 0;
unsigned short LSM_wake_count = 0;


// initialize LCD and define colors
rgb_lcd lcd;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

// other global variables
int counter = 0;
bool alarm_state = 0;
bool buzzer_state = 0;


// function prototypes
void toArduino();
void toLSM();
void toLCD();
int getLSMData();



void setup() {
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  myIMU.begin();
  Serial.begin(115200);
  delay(500);
}



void loop() {

  toArduino();
  delay(300);
  
  toLSM();
  delay(50);
  
  toLCD();
  delay(50);
}



void toArduino()
{
  String outString = "hello";
  
  // send that value to arduino slave
  byte outData[PAYLOADSIZE];
  for (int i = 0; i < PAYLOADSIZE; i++) {
    outData[i] = (byte)outString.charAt(i);
  }
  Wire.beginTransmission(ARD_ADDRESS);
  Wire.write(outData, sizeof(outData));
  Wire.endTransmission();

  // Read response from Slave
  Wire.requestFrom(ARD_ADDRESS, PAYLOADSIZE);
  response = "";
  while (Wire.available()) {
      char b = Wire.read();
      response += b;
  }

  // print the response, which is dependent on the button press
  Serial.print("Response: " );
  Serial.println(response); 
}



void toLSM()
{
  // get accelerometer data
  Wire.beginTransmission(ACC_ADDRESS);
  //Serial.print(" X = ");
  LSMData = getLSMData();
  //Serial.println(accel_val);
  Wire.endTransmission();

  if(LSMData > LSM_WAKE_VAL)
  {
    Serial.print("WakeUp!!!");
    Serial.println(LSMData);
    LSMData = 0;
    LSM_wake_count = 0;
  }

  if(LSM_wake_count == LSM_COUNT_MAX)
  {
    LSMData = 0;
    LSM_wake_count = 0;
    Serial.println("Wake count restarting");
  }
}



void toLCD()
{
  // display the response
  Wire.beginTransmission(LCD_ADDRESS);
  lcd.clear();
  lcd.print("LSM: ");
  lcd.print(response);
  Wire.endTransmission();
}



int getLSMData()
{
  LSM_wake_count++;

  while(curr_LSM_timer - prev_LSM_timer <= LSM_TIMER)
  {
    curr_LSM_timer = millis();
    LSMData += sqrt(abs(myIMU.readFloatAccelX()));
    LSMData += sqrt(abs(myIMU.readFloatAccelY()));
    LSMData += sqrt(abs(myIMU.readFloatAccelZ()));
  }

  Serial.print("LSMData: ");
  Serial.println(LSMData);
  prev_LSM_timer = curr_LSM_timer;
  return LSMData;
}
