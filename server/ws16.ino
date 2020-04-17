char mas[20];
byte b = 0;
void ws16Read() {
  if (ws16.available()) {
    mas[b] = ws16.read();
    b++;
    if (b == 20) {
      //получаем положения релюшек
      if (mas[1] == 12) {
        for (b = 0; b <= 15; b++) {
          structure[b].b = (int(mas[b + 2]) == 1);
        }
      }
      //worksw16 = true;
      b = 0;
      //obTFT();
    }
  }
}
void sw16work() {
  StructList list = listsw16.shift();
  if (list.z == 0)
    sw16send(list.pin, false);
  if (list.z == 1)
    sw16send(list.pin, true);
  if (list.z == 9)
    sw16send(list.pin, !structure[list.pin].b);
}
void sw16send(byte pin, bool z) {
  lastsw16 = millis() + 75;
  char ByteToChar[] = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f";
  if (z == false) {
    ws16.print(String("\xaa\x0f") + char(ByteToChar[pin]) + "\x02\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\xbb");
  }
  if (z == true) {
    ws16.print(String("\xaa\x0f") + char(ByteToChar[pin]) + "\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\xbb");
  }
}
