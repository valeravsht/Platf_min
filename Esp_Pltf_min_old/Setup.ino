
void setup(void) {
  DBG_OUTPUT_PORT.begin(115200);
  DBG_OUTPUT_PORT.setDebugOutput(true);
  DBG_OUTPUT_PORT.print("\n");


  if (SD.begin(chipSelect)) {
    DBG_OUTPUT_PORT.println("SD Card initialized.");
    hasSD = true;
  }

  if (loadConfig1()) {
    DBG_OUTPUT_PORT.println("Load Config 1 - OK");
  } else {
    DBG_OUTPUT_PORT.println("Load Config 1 - BAD!!!!");
  }
  if (loadConfig2()) {
    DBG_OUTPUT_PORT.println("Load Config 2 - OK");
  } else {
    DBG_OUTPUT_PORT.println("Load Config 2 - BAD!!!!");
  }
  if (loadConfig3()) {
    DBG_OUTPUT_PORT.println("Load Config 3 - OK");
  } else {
    DBG_OUTPUT_PORT.println("Load Config 3 - BAD!!!!");
  }
  if (loadConfig4()) {
    DBG_OUTPUT_PORT.println("Load Config 4 - OK");
  } else {
    DBG_OUTPUT_PORT.println("Load Config 4 - BAD!!!!");
  }

  printGlobal();

  // Wire.begin(DS1307_SCL, DS1307_SDA);
  Wire.begin();
  if (wifi_AP) {
    Serial.println();
    Serial.print("Configuring access point...");
    /* You can remove the password parameter if you want the AP to be open. */
    IPAddress AP_ip(staticAPIP1, staticAPIP2, staticAPIP3, staticAPIP4);
    IPAddress AP_mask(staticAPMask1, staticAPMask2, staticAPMask3, staticAPMask4);
    IPAddress AP_gw(staticAPGw1, staticAPGw2, staticAPGw3, staticAPGw4);

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(AP_ip, AP_gw, AP_mask);

    WiFi.softAP(ssidAP.c_str(), passwordAP.c_str());
    uint8_t i = 0;
    while (WiFi.status() != WL_CONNECTED && i++ < 20) {//wait 10 seconds
      delay(500);
    }
    DBG_OUTPUT_PORT.print("Connected! IP address: ");
    DBG_OUTPUT_PORT.println(WiFi.softAPIP());

  } else {
    WiFi.mode(WIFI_STA);
    if (!ipDCHP) {
      IPAddress ip(staticIP1, staticIP2, staticIP3, staticIP4); //static IP address
      IPAddress ip_gate(staticGw1, staticGw2, staticGw3, staticGw4);
      IPAddress ip_subnet(staticMask1, staticMask2, staticMask3, staticMask4);
      IPAddress ip_dns1(dns1_1, dns1_2, dns1_3, dns1_4);
      IPAddress ip_dns2(dns2_1, dns2_2, dns2_3, dns2_4);
      WiFi.config(ip, ip_gate, ip_subnet, ip_dns1, ip_dns2);
    }
    WiFi.begin(ssid.c_str(), password.c_str());
    DBG_OUTPUT_PORT.print("Connecting to ");
    DBG_OUTPUT_PORT.println(ssid);
    // Wait for connection
    uint8_t i = 0;
    while (WiFi.status() != WL_CONNECTED && i++ < 20) {//wait 10 seconds
      delay(500);
    }
    if (i == 21) {
      DBG_OUTPUT_PORT.print("Could not connect to");
      DBG_OUTPUT_PORT.println(ssid);
      while (1) delay(500);
    }
    DBG_OUTPUT_PORT.print("Connected! IP address: ");
    DBG_OUTPUT_PORT.println(WiFi.localIP());

    DBG_OUTPUT_PORT.print("SSID -  ");
    DBG_OUTPUT_PORT.println(WiFi.SSID());
    DBG_OUTPUT_PORT.print("RSSI -  ");
    DBG_OUTPUT_PORT.println(WiFi.RSSI());
    DBG_OUTPUT_PORT.print("macAddress -  ");
    DBG_OUTPUT_PORT.println(WiFi.macAddress());
  }



  server.on("/list", HTTP_GET, printDirectory);
  server.on("/edit", HTTP_DELETE, handleDelete);
  server.on("/edit", HTTP_PUT, handleCreate);
  server.on("/edit", HTTP_POST, []() {
    returnOK();
  }, handleFileUpload);
  server.on("/", homePage);
  server.on("/gettime.json", gTime);
  server.on("/stime", sTime);
  server.on("/gwifi1", gWiFi1);
  server.on("/gwifi2", gWiFi2);
  server.on("/gwifi3", gWiFi3);
  server.on("/gwifi4", gWiFi4);
  server.on("/swifi1",  sWiFi1);
  server.on("/swifi2",  sWiFi2);
  server.on("/swifi3",  sWiFi3);
  server.onNotFound(handleNotFound);

  server.begin();
  DBG_OUTPUT_PORT.println("HTTP server started");

  DBG_OUTPUT_PORT.println("OP");



  // Setup MqttClient
  client.setServer(MqttServer.c_str(), MqttPort.toInt());
  client.setCallback(callback);



  setPin(13, OUTPUT);
  setPin(12, INPUT);
  setPin(11, OUTPUT);
  setPin(10, OUTPUT);



  // таймер взводит переменную flip ЧЕРЕЗ  0.5s ИНТЕРВАЛ
  // flipper.attach(0.5, flips);
  flipper.attach(5, flips);
}

void flips()
{
  //таймер взводит переменную flip ЧЕРЕЗ ЗАДАННЫЙ ИНТЕРВАЛ
  flip = true;
}

