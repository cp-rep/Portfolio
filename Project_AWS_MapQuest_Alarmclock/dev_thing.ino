#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <SoftwareSerial.h>
#include <MQTT.h>
#include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson (use v6.xx)
#include <time.h>
#include <Wire.h>
#define emptyString String()
#include <String>
#include <SPI.h>
#include "rgb_lcd.h"
#include "SparkFunLSM6DS3.h"

//Follow instructions from https://github.com/debsahu/ESP-MQTT-AWS-IoT-Core/blob/master/doc/README.md
//Enter values in secrets.h ▼
#include "secrets.h"

#if !(ARDUINOJSON_VERSION_MAJOR == 6 and ARDUINOJSON_VERSION_MINOR >= 7)
#error "Install ArduinoJson v6.7.0-beta or higher"
#endif

// runtime constants
const int MQTT_PORT = 8883;
const char MQTT_SUB_TOPIC[] = "$aws/things/" THINGNAME "/shadow/update";
//const char MQTT_PUB_TOPIC[] = "$aws/things/" THINGNAME "/shadow/update";
const char MQTT_PUB_TOPIC[] = "lab4_temps";

#ifdef USE_SUMMER_TIME_DST
uint8_t DST = 1;
#else
uint8_t DST = 0;
#endif

BearSSL::WiFiClientSecure net;
BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);

// compile time constants
#define PAYLOADSIZE 5
#define LCD_ADDRESS 0x3c
#define ACC_ADDRESS 0x6b
#define ARD_ADDRESS 0x09
#define MST (-7)
#define UTC (0)
#define CCT (+8)
#define LSM_TIMER 1000
#define LSM_COUNT_MAX 10
#define LSM_WAKE_VAL 600

// initialize accelerometer data
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

// initialize mqtt client
MQTTClient client;

// initialize time data
unsigned long lastMillis = 0;
time_t now;
time_t nowish = 1510592825;

// other global variables
int counter = 0;
bool alarm_state = 0;
bool buzzer_state = 0;
String response = "";

// function prototypes
void toArduino();
void toLSM();
void toLCD();
int getLSMData();



void NTPConnect(void)
{
    Serial.print("Setting time using SNTP");
    configTime(TIME_ZONE * 3600, DST * 3600, "pool.ntp.org", "time.nist.gov");
    now = time(nullptr);
    while (now < nowish)
    {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }
    Serial.println("done!");
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);
    Serial.print("Current time: ");
    Serial.print(asctime(&timeinfo));
    
    // set up the LCD's number of columns and rows
    lcd.begin(24, 1);
    lcd.setRGB(colorR, colorG, colorB);
}



// this gets called when we recieve a message on a topic that we are subscribed to
void messageReceived(String &topic, String &payload)
{
    Serial.println("Recieved [" + topic + "]: " + payload);
}



void lwMQTTErr(lwmqtt_err_t reason)
{
    if (reason == lwmqtt_err_t::LWMQTT_SUCCESS)
        Serial.print("Success");
    else if (reason == lwmqtt_err_t::LWMQTT_BUFFER_TOO_SHORT)
        Serial.print("Buffer too short");
    else if (reason == lwmqtt_err_t::LWMQTT_VARNUM_OVERFLOW)
        Serial.print("Varnum overflow");
    else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_FAILED_CONNECT)
        Serial.print("Network failed connect");
    else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_TIMEOUT)
        Serial.print("Network timeout");
    else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_FAILED_READ)
        Serial.print("Network failed read");
    else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_FAILED_WRITE)
        Serial.print("Network failed write");
    else if (reason == lwmqtt_err_t::LWMQTT_REMAINING_LENGTH_OVERFLOW)
        Serial.print("Remaining length overflow");
    else if (reason == lwmqtt_err_t::LWMQTT_REMAINING_LENGTH_MISMATCH)
        Serial.print("Remaining length mismatch");
    else if (reason == lwmqtt_err_t::LWMQTT_MISSING_OR_WRONG_PACKET)
        Serial.print("Missing or wrong packet");
    else if (reason == lwmqtt_err_t::LWMQTT_CONNECTION_DENIED)
        Serial.print("Connection denied");
    else if (reason == lwmqtt_err_t::LWMQTT_FAILED_SUBSCRIPTION)
        Serial.print("Failed subscription");
    else if (reason == lwmqtt_err_t::LWMQTT_SUBACK_ARRAY_OVERFLOW)
        Serial.print("Suback array overflow");
    else if (reason == lwmqtt_err_t::LWMQTT_PONG_TIMEOUT)
        Serial.print("Pong timeout");
}



void lwMQTTErrConnection(lwmqtt_return_code_t reason)
{
    if (reason == lwmqtt_return_code_t::LWMQTT_CONNECTION_ACCEPTED)
    {
        Serial.println(lwmqtt_return_code_t::LWMQTT_CONNECTION_ACCEPTED);
        Serial.print("Connection Accepted");
    }
    else if (reason == lwmqtt_return_code_t::LWMQTT_UNACCEPTABLE_PROTOCOL)
        Serial.print("Unacceptable Protocol");
    else if (reason == lwmqtt_return_code_t::LWMQTT_IDENTIFIER_REJECTED)
        Serial.print("Identifier Rejected");
    else if (reason == lwmqtt_return_code_t::LWMQTT_SERVER_UNAVAILABLE)
        Serial.print("Server Unavailable");
    else if (reason == lwmqtt_return_code_t::LWMQTT_BAD_USERNAME_OR_PASSWORD)
        Serial.print("Bad UserName/Password");
    else if (reason == lwmqtt_return_code_t::LWMQTT_NOT_AUTHORIZED)
        Serial.print("Not Authorized");
    else if (reason == lwmqtt_return_code_t::LWMQTT_UNKNOWN_RETURN_CODE)
        Serial.print("Unknown Return Code");
}



//Establishes connection to AWS
void connectToMqtt(bool nonBlocking = false)
{
    Serial.print("MQTT connecting ");
    while (!client.connected())
    {
        if (client.connect(THINGNAME))
        {
            Serial.println("connected!");

            //subscribe to a topic
            if (!client.subscribe(MQTT_SUB_TOPIC))
                lwMQTTErr(client.lastError());
        }
        else
        {
            Serial.print("SSL Error Code: ");
            Serial.println(net.getLastSSLError());
            Serial.print("failed, reason -> ");
            lwMQTTErrConnection(client.returnCode());
            if (!nonBlocking)
            {
                Serial.println(" < try again in 5 seconds");
                delay(5000);
            }
            else
            {
                Serial.println(" <");
            }
        }
        if (nonBlocking)
            break;
    }
}



void connectToWiFi(String init_str)
{
    Serial.println("Init Wifi");
    if (init_str != emptyString)
        Serial.print(init_str);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }
    if (init_str != emptyString)
        Serial.println("ok!");
}



void checkWiFiThenMQTT(void)
{
    connectToWiFi("Checking WiFi");
    connectToMqtt();
}

unsigned long previousMillis = 0;
const long interval = 5000;



void checkWiFiThenReboot(void)
{
    connectToWiFi("Checking WiFi");
    Serial.print("Rebooting");
    ESP.restart();
}



void sendData(void)
{
  //const int capacity = JSON_OBJECT_SIZE(3);
  //StaticJsonDocument<capacity> doc;
  DynamicJsonDocument doc(JSON_OBJECT_SIZE(3) + 100);  
  JsonObject root = doc.to<JsonObject>();
  JsonObject state = root.createNestedObject("");
  doc["device"] = "Basic Weather Monitor";
  doc["temp"] = counter++;
  doc["humidity"] = counter += 10;
  int len = measureJson(doc) + 1;
  char buffer[len];
  serializeJson(doc, buffer, sizeof(buffer));
  if(!client.publish(MQTT_PUB_TOPIC, buffer, false, 0 ))
    lwMQTTErr(client.lastError());
}



void setup()
{
    // setup lcd
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
    myIMU.begin();
    
    // start serial communication
    Serial.begin(115200);
    delay(500);
    Serial.println("Begin Setup Procedure");
    Serial.println();
    
    //setup wifi
    WiFi.hostname(THINGNAME);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    delay(500);
  
    //init connection
    connectToWiFi(String("Attempting to connect to SSID: ") + String(ssid));
    NTPConnect();

    // set up the communication certs
    net.setTrustAnchors(&cert);
    net.setClientRSACert(&client_crt, &key);
    
    client.begin(MQTT_HOST, MQTT_PORT, net);
    client.onMessage(messageReceived);

    connectToMqtt();
}



void loop()
{ 
  // get time 
  now = time(nullptr);

  // i2c to arduino
  toArduino();
  delay(300);

  // i2c to LSM
  toLSM();
  delay(50);

  // i2c to LCD
  toLCD();
  delay(50);


  // check that WiFi is still connected, reconnect if disconnected
  if (!client.connected())
  {
    checkWiFiThenMQTT();
  }
  else
  {
    client.loop();
    if (millis() - lastMillis > 5000)
    {
      lastMillis = millis();
      sendData();
    }
  }
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
