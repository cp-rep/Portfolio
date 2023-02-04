#include <Wire.h>

// compile time consants
#define OUT_ANSWERSIZE 5
#define ARD_ADDRESS 0x09

// runtime constants
// define global grove button data
const int buttonPin = 2; // D2 on arduino shield
const int buzzerPin = 3;
bool outVal = 0;

// i2c data
String inString = "slave";
String outString = "evals";

bool alarmState = 0;
bool buzzerState = 0;


void setup() {
  delay(250);
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  Wire.begin(ARD_ADDRESS);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}



void receiveEvent() {
  // DONT PUT DELAY HERE
  inString = "";
  while (0 < Wire.available()) {
    byte x = Wire.read();
    inString += (char)x;
  }
  // DONT PUT DELAY HERE
}



void requestEvent() {
  // DONT PUT DELAY HERE
  if(outVal == 1)
  {
    byte response[OUT_ANSWERSIZE];
    for (int i = 0; i < OUT_ANSWERSIZE; i++) {
      response[i] = (byte)outString.charAt(i);
    }

    Wire.write(response,sizeof(response));

    Serial.println(outString);
  }
  else
  {
    byte response[OUT_ANSWERSIZE];
    for (int i = 0; i < OUT_ANSWERSIZE; i++) {
      response[i] = (byte)inString.charAt(i);
    }

    Wire.write(response,sizeof(response));

    Serial.println(outString);
  }
 // DONT PUT DELAY HERE
}



void loop() {
 if(digitalRead(buttonPin)){
    Serial.print("In String: ");
    Serial.println(inString);
    outVal = 1;
    if(buzzerState == 0)
    {
      digitalWrite(buzzerPin, HIGH);
      buzzerState = 1;
    }
    else
    {
      digitalWrite(buzzerPin, LOW);
      buzzerState = 0;
    }
  }
  else
  {
    outVal = 0;
  }
  delay(300);
}
