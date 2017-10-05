
void testpp() {
  String message = "TEST\n\n";
  server.sendContent(message);
}

void gTime() {
  // tmElements_t tm;
  String json = "{\"year\":\"1900\",\"mounth\":\"01\",\"day\":\"01\",\"hour\":\"0\",\"minut\":\"0\",\"secund\":\"0\"}";
  getDateDs1307();
  //second, minute, hour, dayOfWeek, day, dayOfMonth, month, year;
  json = "{\"year\":\"";
  json += g_year;
  json += "\",\"month\":\"";
  json += g_month;
  json += "\",\"day\":\"";
  json += g_day;
  json += "\",\"hour\":\"";
  json += g_hour;
  json += "\",\"minut\":\"";
  json += g_minute;
  json += "\",\"secund\":\"";
  json += g_second;
  json += "\"}";
  /*  if (RTC.read(tm)) {
        json = "{\"hour\":\"";
        json += tm.Hour;
        json += "\",\"minut\":\"";
        json += tm.Minute;
        json += "\",\"secund\":\"";
        json += tm.Second ;
        json += "\"}";
     }*/
  //server.sendContent(json);
  server.send(200, "text/json", json);
}

void sTime() {


  String message = "";
  //s_second, s_minute, s_hour, s_dayOfWeek, s_day, s_dayOfMonth, s_month, s_year;

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
    String sName =  server.argName(i);
    String sVal = server.arg(i);

    if (sName == "syear") {
      if ( sVal.length() == 4) {
        sVal = sVal.substring(3);
      }
      s_year = (byte)sVal.toInt();
      continue;
    }
    if (sName == "smonth") {
      s_month = (byte)sVal.toInt();
      continue;
    }
    if (sName == "sday") {
      s_day = (byte)sVal.toInt();
      continue;
    }
    if (sName == "shour") {
      s_hour = (byte)sVal.toInt();
      continue;
    }
    if (sName == "sminute") {
      s_minute = (byte)sVal.toInt();
      continue;
    }
    if (sName == "ssecond") {
      s_second = (byte)sVal.toInt();
      continue;
    }
  }
  setDateDs1307();
  DBG_OUTPUT_PORT.print(message);
}

void gWiFi1() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["Mac"] = WiFi.macAddress();
  if (wifi_AP) {
    root["tip_wifi"] = "AP"; //точка доступа
  } else
  {
    root["tip_wifi"] = "Client"; //точка доступа
  }
  root["ssid"] = ssid;
  root["password"] = password;
  if (ipDCHP) {
    root["tip_ip"] = "DCHP";
  } else {
    root["tip_ip"] = "static";
  }
  root["static_ip1"] = staticIP1;
  root["static_ip2"] = staticIP2;
  root["static_ip3"] = staticIP3;
  root["static_ip4"] = staticIP4;

  String output;
  root.printTo(output);
  server.send(200, "text/json", output);

}
void gWiFi2() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();


  root["static_mask1"] = staticMask1;
  root["static_mask2"] = staticMask2;
  root["static_mask3"] = staticMask3;
  root["static_mask4"] = staticMask4;
  root["static_gw1"] = staticGw1;
  root["static_gw2"] = staticGw2;
  root["static_gw3"] = staticGw3;
  root["static_gw4"] = staticGw4;

  String output;
  root.printTo(output);
  server.send(200, "text/json", output);

}

void gWiFi3() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();


  root["ssidAP"] = ssidAP;
  root["passwordAP"] = passwordAP;
  // root["Mac"] = WiFi.macAddress();
  root["staticAP_ip1"] = staticAPIP1;
  root["staticAP_ip2"] = staticAPIP2;
  root["staticAP_ip3"] = staticAPIP3;
  root["staticAP_ip4"] = staticAPIP4;
  root["staticAP_mask1"] = staticAPMask1;
  root["staticAP_mask2"] = staticAPMask2;

  String output;
  root.printTo(output);
  server.send(200, "text/json", output);

}
void gWiFi4() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["staticAP_mask3"] = staticAPMask3;
  root["staticAP_mask4"] = staticAPMask4;
  root["staticAP_gw1"] = staticAPGw1;
  root["staticAP_gw2"] = staticAPGw2;
  root["staticAP_gw3"] = staticAPGw3;
  root["staticAP_gw4"] = staticAPGw4;

  String output;
  root.printTo(output);
  server.send(200, "text/json", output);

}
void sWiFi1() {

  String message = "";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
    String sName =  server.argName(i);
    String sVal = server.arg(i);

    if (sName == "ap") {
      if ( sVal == "1" ) {
        wifi_AP = true;
      } else {
        wifi_AP = false;
      }
      continue;
    }
    if (sName == "dchp") {
      if ( sVal == "1" ) {
        ipDCHP = true;
      } else {
        ipDCHP = false;
      }
      continue;
    }
    if (sName == "name") {
      ssid = sVal;
      continue;
    }
    if (sName == "ps") {
      password = sVal;
      continue;
    }
  }
  DBG_OUTPUT_PORT.println("");
  DBG_OUTPUT_PORT.println("set WIFI part1 ");
  DBG_OUTPUT_PORT.print(message);
  DBG_OUTPUT_PORT.println("");
  saveConfig1();
  saveConfig2();
   saveConfig3();

}
void sWiFi2() {
  String message = "";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
    String sName =  server.argName(i);
    String sVal = server.arg(i);

    if (sName == "ip1") {
      staticIP1 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "ip2") {
      staticIP2 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "ip3") {
      staticIP3 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "ip4") {
      staticIP4 = (byte)sVal.toInt();
      continue;
    }

    if (sName == "mask1") {
      staticMask1 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "mask2") {
      staticMask2 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "mask3") {
      staticMask3 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "mask4") {
      staticMask4 = (byte)sVal.toInt();
      continue;
    }


    if (sName == "gw1") {
      staticGw1 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "gw2") {
      staticGw2 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "gw3") {
      staticGw3 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "gw4") {
      staticGw4 = (byte)sVal.toInt();
      continue;
    }
  }
  DBG_OUTPUT_PORT.println("");
  DBG_OUTPUT_PORT.println("set WIFI part2 ");
  DBG_OUTPUT_PORT.print(message);
  DBG_OUTPUT_PORT.println("");
  saveConfig1();
  saveConfig2();
   saveConfig3();
}
void sWiFi3() {
  String message = "";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
    String sName =  server.argName(i);
    String sVal = server.arg(i);

    if (sName == "ipAP1") {
      staticAPIP1 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "ipAP2") {
      staticAPIP2 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "ipAP3") {
      staticAPIP3 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "ipAP4") {
      staticAPIP4 = (byte)sVal.toInt();
      continue;
    }

    if (sName == "maskAP1") {
      staticAPMask1 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "maskAP2") {
      staticAPMask2 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "maskAP3") {
      staticAPMask3 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "maskAP4") {
      staticAPMask4 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "gwAP1") {
      staticAPGw1 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "gwAP2") {
      staticAPGw2 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "gwAP3") {
      staticAPGw3 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "gwAP4") {
      staticAPGw4 = (byte)sVal.toInt();
      continue;
    }
    if (sName == "nameAP") {
      ssidAP = sVal;
      continue;
    }
    if (sName == "psAP") {
      passwordAP = sVal;
      continue;
    }
  }
  DBG_OUTPUT_PORT.println("");
  DBG_OUTPUT_PORT.println("set WIFI part3 ");
  DBG_OUTPUT_PORT.print(message);
  DBG_OUTPUT_PORT.println("");
  saveConfig1();
  saveConfig2();
   saveConfig3();
}

void homePage() {
  String message = " <!DOCTYPE html>"
                  " <html>"
                  " <head>"
                   "<meta http-equiv=""Content - type"" content=""text / html; charset = utf - 8"">"
                   "    <title>ESP Index</title>"
                   "    <style>"
                   "    body {"
                   "    background-color:white;"
                   "    color:black;"
                    " }"
                    "   </style>"
                     "  <script type=""text / javascript"">"
                      " var xmlHttp=createXmlHttpObject();"

                     "  function onBodyLoad(){"
                     "  console.log(""we are loaded!!"");"
                     "}"
                     "  function createXmlHttpObject(){"
                      " if(window.XMLHttpRequest){"
                      " xmlHttp=new XMLHttpRequest();"
                     "}else{"
                      " xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');"
                    " }"
                     "  return xmlHttp;"
                     "}"
                      " function val(id){"
                      " var v = document.getElementById(id).value;"
                       " return v;"
                     "}"
                      " </script>"
                      " < /head >"
                     "  <body id = ""index"" onload = ""onBodyLoad()"">"
                     "  <h1>ESP8266 Pin Functions </h1>"
                      " <p> MAC: ";
  message +=           WiFi.macAddress();

  message += "             <p><a href = ""/setup.htm"">Настройки </a> <p>"

          "    </body>"
            "  </html> " ;
  server.sendContent(message);
}





