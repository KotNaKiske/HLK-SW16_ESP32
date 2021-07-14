TFT_eSPI tft = TFT_eSPI(135, 240);
void tftStart() {
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 8, 1);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  //tft.println("Start");
}
void tftdraw(String txt, int32_t y, uint16_t color) {
  tft.setTextColor(color, TFT_BLACK);
  tft.drawCentreString(txt, 67, y, 1);
}
void tftPrint(String txt, uint16_t color) {
  if (tft.getCursorY() >= 240)
    tft.setCursor(0, 8, 1);
  tft.setTextColor(color, TFT_BLACK);
  tft.println(txt);
  Serial.println(txt);
  //Serial.println(tft.getCursorY());
}
