void wwwindex() {
  String Button =
    "<button class=\"g\" onclick=\"bb(this)\">&#1042;&#1050;&#1051;&#1070;&#1063;&#1048;&#1058;&#1068;</button>"
    "<button class=\"y10\" onclick=\"bb(this)\">10 &#1052;&#1048;&#1053;&#1059;&#1058;</button>"
    "<button class=\"y20\" onclick=\"bb(this)\">20 &#1052;&#1048;&#1053;&#1059;&#1058;</button>"
    "<button class=\"r\" onclick=\"bb(this)\">&#1042;&#1067;&#1050;&#1051;&#1070;&#1063;&#1048;&#1058;&#1068;</button>";
  String html =
    "<!DOCTYPE HTML><html>\n"
    "<head>\n"
    "<title>Home Server</title>\n"
    "<style>\n"
    "html {font-family: Arial; display: inline-block; text-align: center;}\n"
    "body {background-color: #121212;color: white;}\n"
    "button {color: white; font-weight: bold; border-radius: 12px; padding: 20px 60px; font-size: 20px;}\n"
    "h4 {position: absolute;margin: 0px;padding: 1.33em;}\n"

    ".r {background-color: red;}\n"
    ".g {background-color: green;}\n"
    ".y10, .y20, .y {background-color: yellowgreen;}\n"
    ".o {padding: 0px;font-size: 20px;position: fixed;right: 20%;background-color: darkblue;width: 28px;}\n"
    "</style>\n"
    "</head>\n"
    "<body>\n"
    "<button class=\"o\" onclick=\"oo()\">&#x21bb;</button>"
    "<h4 style=\"position: static;\">Home Server</h4>"
    "<div id=3><h4>" + structure[3].s + "</h4>" + Button + "</div>\n"
    "<div id=7><h4>" + structure[7].s + "</h4>" + Button + "</div>\n"
    "<div id=11><h4>" + structure[11].s + "</h4>" + Button + "</div>\n"
    "<div id=16><h4>&#1047;&#1040;&#1051;(&#1057;&#1042;&#1045;&#1058;&#1054;&#1044;&#1048;&#1054;&#1044;&#1067;)</h4>" + Button + "</div>\n"
    "<div id=13><h4>" + structure[13].s + "</h4>" + Button + "</div>\n"
    "<div id=15><h4>" + structure[15].s + "</h4>" + Button + "</div>\n"
    "<script>function bb(element) {\n"
    "var xhr = new XMLHttpRequest();\n"
    "xhr.open(\"GET\", \"/sw/\"+element.parentNode.id+\"/\"+element.classList[0], true);\n"
    "xhr.send();}\n"

    "function oo() {\n"
    "var xhr = new XMLHttpRequest();\n"
    "xhr.open('GET', \"/status\");"
    "xhr.onloadend = function() {"
    "parse(xhr.responseText);"
    "};\n"
    "xhr.send();"
    "}\n"
    "function parse(obj) {\n"
    "var DATA = JSON.parse(obj);\n"
    "if(DATA[\"stat\"][3]==1) {document.getElementById('3').firstChild.style=\"background-color: green;\";} else {document.getElementById('3').firstChild.style=\"background-color: red;\"};\n"
    "if(DATA[\"stat\"][7]==1) {document.getElementById('7').firstChild.style=\"background-color: green;\";} else {document.getElementById('7').firstChild.style=\"background-color: red;\"};\n"
    "if(DATA[\"stat\"][11]==1) {document.getElementById('11').firstChild.style=\"background-color: green;\";} else {document.getElementById('11').firstChild.style=\"background-color: red;\"};\n"
    "if(DATA[\"stat\"][10]==1) {document.getElementById('16').firstChild.style=\"background-color: green;\";} else {document.getElementById('16').firstChild.style=\"background-color: red;\"};\n"
    "if(DATA[\"stat\"][13]==1) {document.getElementById('13').firstChild.style=\"background-color: green;\";} else {document.getElementById('13').firstChild.style=\"background-color: red;\"};\n"
    "if(DATA[\"stat\"][15]==1) {document.getElementById('15').firstChild.style=\"background-color: green;\";} else {document.getElementById('15').firstChild.style=\"background-color: red;\"};\n"
    "console.log(DATA);"
    "}\n"
    "</script>\n"
    "</body>\n"
    "</html>\n";
  www.send(200, "text/html", html);
}
void wwwstatus() {
  String s;
  s = "{\"stat\":[";
  for (int i = 0; i <= 15; i++) {
    if (structure[i].b)
      s += "1";
    else
      s += "0";
    if (i != 15)
      s += ",";
  }
  s += "],\"millis\": \"" + String(millis()) + "\"}";
  www.send(200, "application/json", s);
}
void wwwsw() {
  if (www.pathArg(1) == "r") {
    if ((www.pathArg(0)).toInt() == 16) {
      listsw16.add({8, false});
      listsw16.add({10, false});
      listsw16.add({12, false});
      listsw16.add({14, false});
    } else
      listsw16.add({(www.pathArg(0)).toInt(), false});
  }
  else if ((www.pathArg(1) == "g") || (www.pathArg(1) == "y10") || (www.pathArg(1) == "y20")) {
    if ((www.pathArg(0)).toInt() == 16) {
      listsw16.add({8, true});
      listsw16.add({10, true});
      listsw16.add({12, true});
      listsw16.add({14, true});
    } else
      listsw16.add({(www.pathArg(0)).toInt(), true});
  }
  if (www.pathArg(1) == "y10") {
    if ((www.pathArg(0)).toInt() == 16) {
      structure[14].timeroff = millis() + 600000;
      structure[12].timeroff = millis() + 600000;
      structure[10].timeroff = millis() + 600000;
      structure[8].timeroff = millis() + 600000;
    } else
      structure[(www.pathArg(0)).toInt()].timeroff = millis() + 600000;
  }
  if (www.pathArg(1) == "y20") {
    if ((www.pathArg(0)).toInt() == 16) {
      structure[14].timeroff = millis() + 1200000;
      structure[12].timeroff = millis() + 1200000;
      structure[10].timeroff = millis() + 1200000;
      structure[8].timeroff = millis() + 1200000;
    } else
      structure[(www.pathArg(0)).toInt()].timeroff = millis() + 1200000;
  }
  www.send(200, "text/plain", "" + www.pathArg(0) + "|" + www.pathArg(1));
}
void wwwStart() {
  www.on("/", wwwindex);
  www.on("/status", wwwstatus);
  www.on(UriBraces("/sw/{}/{}"), wwwsw);
  /*
    www.on("/info", wwwinfo);
    www.on("/servo", wwwservo);
    www.on("/setting", wwwsetting);/**/
  www.begin();
}
