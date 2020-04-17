void wwwstatus() {
  Serial.println("www connected");
  String s;
  s = "<html><head><title>ESP32 Web Server</title>\
  <link rel=\"stylesheet\" href=\"//code.jquery.com/ui/1.12.1/themes/base/jquery-ui.css\">\
  <link rel=\"stylesheet\" href=\"/resources/demos/style.css\">\
  <script src=\"https://code.jquery.com/jquery-1.12.4.js\"></script>\
  <script src=\"https://code.jquery.com/ui/1.12.1/jquery-ui.js\"></script>\
  </head><body>";
  for (int i = 0; i <= 15; i++) {
    if (structure[i].b)
      s += "<button id=\"button\" class=\"ui-button ui-corner-all ui-widget\" style=\"color: #4caf50;\">";
    else
      s += "<button id=\"button\" class=\"ui-button ui-corner-all ui-widget\" style=\"color: #f44336;\">";
    s += String(i);
    if (structure[i].timeron != -1)
      s += " " + String(structure[i].timeron - millis());
    else
      s += " -";
    if (structure[i].timeroff != -1)
      s += " " + String(structure[i].timeroff - millis());
    else
      s += " -";
    s += "</button><br>";
  }
  s += "</body></html>";
  www.send(200, "text/html", s);
}
void wwwsetting() {
  String s = "";
  www.send(200, "text/plain", s);
}
void wwwsw() {
  www.send(200, "text/plain", "" + www.pathArg(0) + "|" + www.pathArg(1));
  listsw16.add({(www.pathArg(0)).toInt(), (www.pathArg(1)).toInt()});
}
