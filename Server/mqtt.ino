EspMQTTClient mqtt(
  "192.168.0.1",
  1883,
  "",
  "",
  "Home Server"
);
void onConnectionEstablished()
{
  mqtt.subscribe("Blazer", [](const String & topic, const String & payload) {
    //vTaskResume(xBlazer);
  });
  mqtt.subscribe("power", [](const String & topic, const String & payload) {
    float battery_voltage = ((float)analogRead(34) / 4095.0) * 2.0 * 3.3 * (1100 / 1000.0);
    mqtt.publish("ESP/power", "Voltage :" + String(round(battery_voltage * 100) / 100) + "V|" + String(millis()));
  });
  /*mqtt.subscribe("#", [](const String & topic, const String & payload) {
    //Serial.println("(mqtt) topic: " + topic + ", payload: " + payload);
    if (topic.substring(0, 2) == "sw") {
      listsw16.add({topic.substring(2, 2).toInt(), topic.substring(4, 1).toInt()});
      structure[topic.substring(2, 2).toInt()].timeroff = millis() + topic.substring(5).toInt();
    }
    });*/
}
void task_mqtt( void * parameter ) {
  while (true)
  {
    mqtt.loop();
    vTaskDelay(1 / portTICK_RATE_MS);
  }
}
void task_sendmqtt( void * parameter ) {
  String S = "";
  vTaskDelay(2000 / portTICK_RATE_MS);
  while (true) {
    S = "";
    for (int i = 0; i < 16; i++) {
      if (structure[i].b)
        S += "1";
      else
        S += "0";
      S += "|";
      if (structure[i].timeron != -1)
        S += structure[i].timeron;
      S += "|";
      if (structure[i].timeroff != -1)
        S += structure[i].timeroff;
      S += "|";
    }
    mqtt.publish("ESP/S", S);
    /*float battery_voltage = ((float)analogRead(ADC_PIN) / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
      mqtt.publish("ESP/power", "Voltage :" + String(round(battery_voltage * 100) / 100) + "V|" + String(millis()));*/
    vTaskDelay(1000 / portTICK_RATE_MS);
  }
}
