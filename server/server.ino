#include <Button2.h>

#include <LinkedList.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WebServer.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <esp_adc_cal.h>
#include <WebServer.h>
#include <Esp32MQTTClient.h>

//char txtlog[13][12];
String txtlog[13];

//0,35,//21, 22, 17, 2, 15, 13, 12,//36, 37, 38, 39, 32, 33, 25, 26, 27
Button2 button[12] = {Button2(0), Button2(35), Button2(21), Button2(22), Button2(17), Button2(2), Button2(15), Button2(13), Button2(12),
                      /*, Button2(36), Button2(37), Button2(38), Button2(39), Button2(32), Button2(33),*/ Button2(25, INPUT, false), Button2(33, INPUT, false), Button2(32, INPUT, false)
                     };
//хрень для дисплея
#define TFT_MOSI            19
#define TFT_SCLK            18
#define TFT_CS              5
#define TFT_DC              16
#define TFT_RST             23

#define ADC_PIN         34//замернапряжения
int vref = 1100;
TFT_eSPI tft = TFT_eSPI(135, 240);
//моё управление
struct structure {
  bool b;
  String s;
  long timeron;
  long timeroff;
};
class StructList {
  public:
    byte pin;
    byte z;
};

LinkedList<StructList> listsw16;
long pindown[40];
WebServer www(80);
structure structure[16] =  {
  {false, "", -1, -1}, {false, "Свалка", -1, -1}, {false, "", -1, -1}, {false, "Спальня", -1, -1}, {false, "", -1, -1}, {false, "Коридор", -1, -1}, {false, "", -1, -1}, {false, "кухня", -1, -1},
  {false, "", -1, -1}, {false, "Зал", -1, -1}, {false, "", -1, -1}, {false, "Зал2", -1, -1}, {false, "", -1, -1}, {false, "Ванная", -1, -1}, {false, "", -1, -1}, {false, "туалет", -1, -1}
};

WiFiClient ws16;

const char* ssid = "A";
const char* password = "1234554321";

TaskHandle_t Task1;

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  for (int i = 0; i < 9; i++) {
    button[i].setTapHandler(clickup);
  }
  for (int i = 9; i < 12; i++) {
    button[i].setPressedHandler(clickup);
  }


  OTAStart();
  TFTStart();
  WWWStart();
  ws16Start();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //obTFT();
  xTaskCreatePinnedToCore(
    obTask,   /* Функция задачи */
    "Task1",     /* Название задачи */
    20000,       /* Размер стека задачи */
    NULL,        /* Параметр задачи */
    1,           /* Приоритет задачи */
    &Task1,      /* Идентификатор задачи, sчтобы ее можно было отслеживать */
    0);          /* Ядро для выполнения задачи (0) */
}
long ms, lastms, lastsw16 = 0;
bool worksw16 = true;
void loop() {
  ArduinoOTA.handle();
  for (int i = 0; i < 12; i++) {
    button[i].loop();
  }
}
