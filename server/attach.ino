void clickup(Button2& btn) {
  unsigned int time = btn.wasPressedFor();
  addlog(String("PIN->" + String(btn.getPin())) + "|" + String(btn.getNumberOfClicks()) + "|" + String(time));
  if (btn == button[0]) {
    listsw16.add({7, 1});
    listsw16.add({9, 1});
    structure[7].timeroff = millis() + 600000;
    structure[9].timeroff = millis() + 600000;
  }
  if (btn == button[1]) {
    listsw16.add({7, 0});
    listsw16.add({9, 0});
    structure[7].timeroff = -1;
    structure[9].timeroff = -1;
  }
  if (btn == button[3]) {//зал
    if (btn.getNumberOfClicks() == 2) {
      listsw16.add({7, 0});
      listsw16.add({9, 0});
      structure[7].timeroff = -1;
      structure[9].timeroff = -1;
    } else {
      listsw16.add({7, 1});
      listsw16.add({9, 1});
      if (time > 2000) {
        structure[7].timeroff = millis() + 3600000;
        structure[9].timeroff = millis() + 3600000;
      } else {
        structure[7].timeroff = millis() + 600000;
        structure[9].timeroff = millis() + 600000;
      }

    }
  }
  if (btn == button[4]) {//кухня
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
  if (btn == button[5]) {//спальня
    listsw16.add({3, 9});
  }
  if (btn == button[10]) {//туалет
    listsw16.add({15, 1});
    structure[15].timeroff = millis() + 60000;
  }
  if (btn == button[9]) {//корридор
    listsw16.add({5, 1});
    structure[5].timeroff = millis() + 20000;
  }
}
