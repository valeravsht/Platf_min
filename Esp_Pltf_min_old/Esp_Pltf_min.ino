/*
  SDWebServer - Example WebServer with SD Card backend for esp8266

  Copyright (c) 2015 Hristo Gochkov. All rights reserved.
  This file is part of the ESP8266WebServer library for Arduino environment.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Have a FAT Formatted SD Card connected to the SPI port of the ESP8266
  The web root is the SD Card root folder
  File extensions with more than 3 charecters are not supported by the SD Library
  File Names longer than 8 charecters will be truncated by the SD library, so keep filenames shorter
  index.htm is the default index (works on subfolders as well)

  upload the contents of SdRoot to the root of the SDcard and access the editor by going to http://esp8266sd.local/edit

*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <ArduinoJson.h>
/*
  // Enable MqttClient logs
  #define MQTT_LOG_ENABLED 1
  // Include library
  #include <MqttClient.h>
  #define LOG_PRINTFLN(fmt, ...)  logfln(fmt, ##__VA_ARGS__)
  #define LOG_SIZE_MAX 128
*/
#include <PubSubClient.h> //MQTT

#include <Ticker.h>

Ticker flipper;     //таймер взводит переменную flip ЧЕРЕЗ ЗАДАННЫЙ ИНТЕРВАЛ
bool flip =  false;


#define DBG_OUTPUT_PORT Serial

//const char* tssid = "shintorg1";
//const char* tpassword = "qwerty123";
//const char* host = "esp8266sd";



//******* MQTT  ******************

static String  MQTT_TOPIC = "vlrdev/";

static String MqttClName = ""; // имя клинтна MQTT
static String MqttServer = ""; //сервер брокера MQTT
static String MqttPort = ""; // порт брокера MQTT
static String MqttLogin = "";
static String MqttPaswd = "";


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
//***********************************




// WiFi
String ssid = ""; //имя точки доступа для подключения (режим клиент)
String password = ""; // пароль для подключения (режим клиент)
boolean ipDCHP = true; // получение IP адреса по DCHP

boolean wifi_AP = true; // режимы wifi  false-клиент, true-точка доступа
String ssidAP = ""; // имя для точки доступа (режим точка доступа)
String passwordAP = ""; // пароль для точки доступа (режим точка доступа)
byte staticIP1 ; // статический IP
byte staticIP2 ; // статический IP
byte staticIP3 ; // статический IP
byte staticIP4 ; // статический IP
byte staticMask1 ; // статический Mask
byte staticMask2; // статический Mask
byte staticMask3 ; // статический Mask
byte staticMask4; // статический Mask
byte staticGw1 ; // статический GW
byte staticGw2; // статический GW
byte staticGw3 ; // статический GW
byte staticGw4 ; // статический GW

byte staticAPIP1 ; // статический IP Точки доступа
byte staticAPIP2; // статический IP Точки доступа
byte staticAPIP3; // статический IP Точки доступа
byte staticAPIP4 ; // статический IP Точки доступа
byte staticAPMask1 ; // статический Mask Точки доступа
byte staticAPMask2 ; // статический Mask Точки доступа
byte staticAPMask3 ; // статический Mask Точки доступа
byte staticAPMask4 ; // статический Mask Точки доступа
byte staticAPGw1 ; // статический GW Точки доступа
byte staticAPGw2; // статический GW Точки доступа
byte staticAPGw3 ; // статический GW Точки доступа
byte staticAPGw4 ; // статический GW Точки доступа

const byte dns1_1 = 8 ; //
const byte dns1_2  = 8; //
const byte dns1_3  = 8 ; //
const byte dns1_4  = 8; //

const byte dns2_1 = 8 ; //
const byte dns2_2  = 8; //
const byte dns2_3  = 8 ; //
const byte dns2_4  = 8; //

const int chipSelect = 2; // номер pin для доступа к SD

ESP8266WebServer server(80);

static bool hasSD = false;
File uploadFile;

//***DS1307**********************************************************
//#define DS1307_CTRL_ID 0x68
int clockAddress = 0x68;  // This is the I2C address
byte g_second, g_minute, g_hour, g_dayOfWeek, g_day, g_dayOfMonth, g_month, g_year;
byte s_second, s_minute, s_hour, s_dayOfWeek, s_day, s_dayOfMonth, s_month, s_year;
//#define DS1307_SCL 4
//#define DS1307_SDA 5
//******************************************************************

//*** Arduino Pro I2C **************************************************
//#define ArduinoPro 0x8  // address Arduino Pro I2C
int ArduinoAddress = 0x8;
//******************************************************************

int tmp_int = 0;
void loop(void) {
  server.handleClient();

  // ********* MQTT **************
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  //***************************

  //  loopMqtt();


  if (flip) { // ЗАДАННЫЙ ИНТЕРВАЛ пришел
    flip = false;
   Serial.println("FLIPPP!!!!!");
    //   int b = DigInp(12);
    //   snprintf (msg, sizeof(msg), " 12 = %d  ", b);
    //Serial.println(msg);

//    if (tmp_int == 0) {
//      DigOut(13, LOW);
//      Serial.println(" DigOut(11, LOW);");
//      //  delay(100);
////      DigOut(11, LOW);
////      Serial.println(" DigOut(11, LOW);");
////      DigOut(13, LOW);
////      Serial.println(" DigOut(13, LOW);");
//      tmp_int = 1;
//    } else {
//      DigOut(13, HIGH);
//      Serial.println(" DigOut(11, HIGH);");
//  //    DigOut(11, HIGH);
////      Serial.println(" DigOut(11, HIGH);");
////      DigOut(13, HIGH);
////      Serial.println(" DigOut(13, HIGH);");
//        tmp_int = 0;
//    }

    //    int e = AnalogInp(14);
    //    int f =  AnalogInp(15);
    //     snprintf (msg, sizeof(msg), "A0=%d, A1=%d", e,f);
    //    //    Serial.print("Publish message: ");
    //        Serial.println(msg);

    //    value++;
    //    snprintf (msg, sizeof(msg), "%ld", value);
    //    Serial.print("Publish message: ");
    //    Serial.println(msg);
    //    String outTopic =  MQTT_TOPIC + MqttClName ;
    //    outTopic += "/inp1";
    //    client.publish(outTopic.c_str(), msg);

  }
}
