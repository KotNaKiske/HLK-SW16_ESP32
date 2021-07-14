#include <WiFi.h>
#include <LinkedList.h>
#include <AsyncTCP.h>
#include <TFT_eSPI.h>
#include <WebServer.h>
#include <uri/UriBraces.h>
#include "Button.h"
#include <ArduinoOTA.h>
#include "EspMQTTClient.h"

WebServer www(80);
Button button[8] = {Button(0), Button(35), Button(15), Button(2), Button(21), Button(38), Button(26), Button(33)};
struct structure {
  bool b;
  String s;
  long timeron;
  long timeroff;
  bool blazer;
};
structure structure[16] =  {
  {false, "", -1, -1}, {false, "&#1057;&#1074;&#1072;&#1083;&#1082;&#1072;", -1, -1/*Свалка*/}, {false, "", -1, -1}, {false, "&#1057;&#1055;&#1040;&#1051;&#1068;&#1053;&#1071;", -1, -1/*Спальня*/},
  {false, "", -1, -1}, {false, "&#1050;&#1054;&#1056;&#1048;&#1044;&#1054;&#1056;", -1, -1/*Коридор*/}, {false, "", -1, -1}, {false, "&#1050;&#1059;&#1061;&#1053;&#1071;", -1, -1}/*кухня*/,
  {false, "", -1, -1}, {false, "&#1047;&#1040;&#1051;", -1, -1/*Зал*/}, {false, "", -1, -1}, {false, "&#1047;&#1040;&#1051;", -1, -1/*Зал*/},
  {false, "", -1, -1}, {false, "&#1042;&#1040;&#1053;&#1053;&#1040;&#1071;", -1, -1/*Ванная*/}, {false, "", -1, -1}, {false, "&#1058;&#1059;&#1040;&#1051;&#1045;&#1058;", -1, -1/*туалет*/}
};
class StructList {
  public:
    byte pin;
    byte z;
};
LinkedList<StructList> listsw16;
TaskHandle_t xServo;
void setup()
{
  Serial.begin(2000000);
  tftStart();
  WiFiStart();
  OTAStart();
  wwwStart();
  for (int i = 0; i < 6; i++) {
    button[i].setPressedHandler(clickup);
  }
  for (int i = 6; i < 8; i++) {
    button[i].setTapHandler(clickup);
  }
  xTaskCreatePinnedToCore(task_ws16, "task_ws16", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(task_button, "task_button", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(task_structure, "task_structure", 20000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(task_servo, "task_servo", 10000, NULL, 1, &xServo, 0);
  xTaskCreatePinnedToCore(task_mqtt, "task_mqtt", 10000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(task_sendmqtt, "task_sendmqtt", 10000, NULL, 1, NULL, 0);
}

void loop()
{
  ArduinoOTA.handle();
  www.handleClient();
}
