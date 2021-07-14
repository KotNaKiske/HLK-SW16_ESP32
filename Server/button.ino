void clickup(Button& btn) {
  unsigned int time = btn.wasPressedFor();
  tftPrint(String(millis()) + String(" PIN->" + String(btn.getPin())) + String(digitalRead(btn.getPin())), TFT_GREEN);
  if (btn == button[0]) {
  }
  if (btn == button[1]) {
    vTaskResume(xServo);
  }
  if (btn == button[3]) {//зал
    if (!structure[7].b) {
      listsw16.add({7, 1});
      listsw16.add({8, 1});
      listsw16.add({10, 1});
      listsw16.add({12, 1});
      listsw16.add({14, 1});
      if (time > 2000) {
        structure[7].timeroff = millis() + 3600000;
        structure[8].timeroff = millis() + 3600000;
        structure[10].timeroff = millis() + 3600000;
        structure[12].timeroff = millis() + 3600000;
        structure[14].timeroff = millis() + 3600000;
      } else {
        structure[7].timeroff = millis() + 600000;
        structure[8].timeroff = millis() + 600000;
        structure[10].timeroff = millis() + 600000;
        structure[12].timeroff = millis() + 600000;
        structure[14].timeroff = millis() + 600000;
      }
    } else {
      listsw16.add({7, 0});
      listsw16.add({8, 0});
      listsw16.add({10, 0});
      listsw16.add({12, 0});
      listsw16.add({14, 0});
      structure[7].timeroff = -1;
      structure[8].timeroff = -1;
      structure[10].timeroff = -1;
      structure[12].timeroff = -1;
      structure[14].timeroff = -1;
    }
  }
  if (btn == button[2]) {//кухня ванная
    if (!structure[7].b) {
      listsw16.add({7, 1});
      structure[7].timeron = -1;
      if (time > 2000)
        structure[7].timeroff = millis() + 3600000;
      else
        structure[7].timeroff = millis() + 600000;
      listsw16.add({13, 0});
      structure[13].timeron = -1;
      structure[13].timeroff = -1;
    } else {
      if (structure[7].timeroff < millis() + 60000)
        if (time > 2000)
          structure[7].timeroff = millis() + 3600000;
        else
          structure[7].timeroff = millis() + 600000;
      else {
        listsw16.add({13, 1});
        structure[13].timeron = -1;
        structure[13].timeroff = -1;
        listsw16.add({7, 0});
        structure[7].timeron = -1;
        structure[7].timeroff = -1;
      }
    }
  }
  if (btn == button[4]) {//спальня
    listsw16.add({3, 9});
  }
  if (btn == button[6]) {//туалет
    listsw16.add({15, 1});
    structure[15].timeroff = millis() + 60000;
  }
  if (btn == button[7]) {//корридор
    listsw16.add({5, 1});
    structure[5].timeroff = millis() + 20000;
  }
}
void task_button( void * parameter ) {
  while (true)
  {
    for (int i = 0; i < 8; i++) {
      button[i].loop();
    }
    vTaskDelay(1 / portTICK_RATE_MS);
  }
}
