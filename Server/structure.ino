long  lastms = 0;
void task_structure( void * parameter ) {
  while (true)
  {
    if (millis() < 1000)
      lastms = 0;
    if (millis() > lastms) {
      lastms = millis() + 1000;
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
    vTaskDelay(100 / portTICK_RATE_MS);
  }
}
