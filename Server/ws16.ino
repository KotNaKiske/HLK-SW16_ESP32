WiFiClient ws16;
long  lastsw16 = 0;
byte errorws16;
void ws16Start() {
  IPAddress server(192, 168, 0, 254);
  errorws16 = 0;
  while (!(ws16.connect(server, 8080)))
  {
    tftPrint("ws16 error " + errorws16, TFT_RED);
    errorws16++;
    if (errorws16 == 1) {
      ESP.restart();
    }
  }
  errorws16 = 0;
  tftPrint("ws16 connected", TFT_GREEN);
  ws16.print("\xaa\x1e\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\xbb");//запрос состояния
}
void task_ws16( void * parameter ) {
  ws16Start();
  while (true)
  {
    if (!ws16.connected()) {
      tftPrint("ws16 error", TFT_RED);
      ws16Start();
    }
    byte readstatus = 0;
    if (lastsw16 < millis() & (listsw16.size() > 0)) {
      sw16work();
    }
    while (ws16.available()) {
      char c = ws16.read();
      // ⸮=204 =12
      //⸮=204 =31
      /*Serial.print(c);
        Serial.print("=");
        Serial.print(int(c));
        Serial.print(" ");/**/
      if (c == 221) {
        //Serial.println("");
        readstatus = 0;
        continue;
      }
      if (c == 204) {
        readstatus = 1;
        continue;
      }
      if (readstatus == 1) {
        if (c == 12) {
          lastsw16 = 0;
          readstatus = 2;
        }
        else
          readstatus = 0;
        continue;
      }
      if ((readstatus > 1) & (readstatus < 18)) {
        structure[readstatus - 2].b = (int(c) == 1);
        readstatus++;
        continue;
      }
    }
    vTaskDelay(1 / portTICK_RATE_MS);
  }
}
void sw16work() {
  StructList list = listsw16.shift();
  if (list.z == 0) {
    sw16send(list.pin, false);
    structure[list.pin].timeroff = 0;
    if (list.pin == 15) {
      vTaskResume(xServo);
    }
  }
  if (list.z == 1)
    sw16send(list.pin, true);
  if (list.z == 9)
    sw16send(list.pin, !structure[list.pin].b);
}

void sw16send(byte pin, bool z) {
  lastsw16 = millis() + 175;
  tftPrint("ws16 " + String(pin) + " " + String(z), TFT_PURPLE);
  char ByteToChar[] = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f";
  if (z == false) {
    ws16.print(String("\xaa\x0f") + char(ByteToChar[pin]) + "\x02\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\xbb");
  }
  if (z == true) {
    ws16.print(String("\xaa\x0f") + char(ByteToChar[pin]) + "\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\xbb");
  }/**/
  //ws16.print(String("\xaa\x1a\x02\x02\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\xbb"));
  //ws16.print(String("\xaa\x0f\x01\x02\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\xbb"));
}
