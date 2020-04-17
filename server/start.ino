void OTAStart() {
  ArduinoOTA.setHostname("esp32-Server");

  ArduinoOTA
  .onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else
      type = "filesystem";
    Serial.println("Start updating " + type);
  })
  .onEnd([]() {
    Serial.println("\nEnd");
  })
  .onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  })
  .onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.begin();
}
void ws16Start() {
  IPAddress server(192, 168, 0, 254);
  if (ws16.connect(server, 8080))
  {
    Serial.println("ws16 connected");
    ws16.print("\xaa\x1e\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\xbb");//запрос состояния
  }
  else
    esp_restart();
}
void WWWStart() {
  www.on("/", wwwstatus);
  www.on("/setting", wwwsetting);
  www.on("/sw/{}/{}", wwwsw);
  www.begin();
}
void TFTStart() {
  tft.init();
  tft.setSwapBytes(true);
  tft.setRotation(2);
  int i = 5;
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.setTextSize(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(TL_DATUM);
}
void obTask( void * parameter ) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(TL_DATUM);
  tft.setTextSize(1);
  for (;;) {
    delay(1);
    if (!ws16.connected()) {
      addlog(String("ws16 error"));
      IPAddress server(192, 168, 0, 254);
      if (ws16.connect(server, 8080))
      {
        Serial.println("ws16 connected");
        ws16.print("\xaa\x1e\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\xbb");//запрос состояния
      }
    }
    obTFT();
    www.handleClient();
    ws16Read();
    ms = millis();
    if (lastsw16 < ms & (listsw16.size() > 0))
      sw16work();
    if (ms < 1000)
      lastms = 0;
    if (ms > lastms) {
      lastms = ms + 1000;
      for (byte i = 0; i < 16; i++) {
        if (structure[i].timeroff != -1)
          if (structure[i].timeroff < lastms) {
            structure[i].timeroff = -1;
            if (structure[i].b) {
              listsw16.add({i, 0});
            }
          }
        if (structure[i].timeron != -1)
          if (structure[i].timeron < lastms) {
            structure[i].timeron = -1;
            if (!structure[i].b) {
              listsw16.add({i, 1});
            }
          }
      }
    }
  }
}
void addlog(String txt) {
  for (byte i = 12; i > 0; i--) {
    txtlog[i] = txtlog[i - 1];
  }
  for (byte i = txt.length(); i <= 21; i++)
    txt += " ";
  txtlog[0] = txt;
}
void obTFT() {
  tft.setCursor(0, 0);
  for (byte i = 0; i <= 15; i++) {
    if (structure[i].b)
      tft.setTextColor(TFT_GREEN, TFT_BLACK);
    else
      tft.setTextColor(TFT_RED, TFT_BLACK);
    if (String(i).length() == 1)
      tft.print("0");
    tft.print(String(i));
    if (structure[i].timeron != -1) {
      tft.print(" ");
      for (byte j = 1; j <= 8 - String(structure[i].timeron - millis()).length(); j++)
        tft.print("-");
      tft.print(String(structure[i].timeron - millis()));
    }
    else
      tft.print(" --------");
    if (structure[i].timeroff != -1) {
      tft.print(" ");
      for (byte j = 1; j <= 8 - String(structure[i].timeroff - millis()).length(); j++)
        tft.print("-");
      tft.print(String(structure[i].timeroff - millis()));
    }
    else
      tft.print(" --------");
    tft.println("");
  }//13 строк для лога
  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
  for (byte i = 0; i <= 12; i++) {
    tft.println(String(txtlog[i]));
  }
  float battery_voltage = ((float)analogRead(ADC_PIN) / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
  String voltage = "Voltage :" + String(round(battery_voltage * 100) / 100) + "V|" + String(millis());
  for (byte i = voltage.length(); i <= 21; i++)
    tft.print(" ");
  tft.println(voltage);
}
