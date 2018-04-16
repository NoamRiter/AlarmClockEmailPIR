void Portfolio() {
  javascriptPortfolio();
  getHeader();
webpage += "<br />\n";
        webpage += "<div class=\"row\">\n";
           webpage += "<div class=\"col-md-12 col-sm-12 text-center\">\n";
              webpage += "<input id=\"9\" type=\"time\" onchange=\"saveTime(this)\" value=\"" + String(AlarmHour) + ":" + String(AlarmMin) + "\">\n";
           webpage += "</div>\n";
        webpage += "</div>\n";
        webpage += "<br />\n";
        webpage += "<br />\n";
webpage += "<div class=\"container\">\n";
 webpage += "<div class=\"row\">\n";
 
       webpage += "<div class=\"col-md-1 col-sm-1\">\n";
                  if (day1[0] == '1')
                  {
                    webpage += "<input id=\"2\" onchange=\"saveData(this)\" type=\"checkbox\" checked>\n";
                  }
                  else
                  {
                    webpage += "<input id=\"2\" onchange=\"saveData(this)\" onchange=\"saveData(this)\" type=\"checkbox\">\n";
                  }
                  webpage += "<label style=\"color:red\" for=\"a\">S&ouml;ndag</label>\n";
       webpage += "</div>\n";

        webpage += "<div class=\"col-md-1 col-sm-1\">\n";
                  if (day2[0] == '1')
                  {
                    webpage += "<input id=\"3\" onchange=\"saveData(this)\" type=\"checkbox\" checked>\n";
                  }
                  else
                  {
                    webpage += "<input id=\"3\" onchange=\"saveData(this)\" type=\"checkbox\">\n";
                  }
                  webpage += "<label style=\"color:red\" for=\"b\">M&aring;ndag</label>\n";
       webpage += "</div>\n";

       webpage += "<div class=\"col-md-1 col-sm-1\">\n";
                  if (day3[0] == '1')
                  {
                    webpage += "<input id=\"4\" onchange=\"saveData(this)\" type=\"checkbox\" checked>\n";
                  }
                  else
                  {
                    webpage += "<input id=\"4\" onchange=\"saveData(this)\" type=\"checkbox\">\n";
                  }
                  webpage += "<label style=\"color:red\" for=\"c\">Tisdag</label>\n";
       webpage += "</div>\n";

        webpage += "<div class=\"col-md-1 col-sm-1\">\n";
                  if (day4[0] == '1')
                  {
                    webpage += "<input id=\"5\" onchange=\"saveData(this)\" type=\"checkbox\" checked>\n";
                  }
                  else
                  {
                    webpage += "<input id=\"5\" onchange=\"saveData(this)\" type=\"checkbox\">\n";
                  }
                  webpage += "<label style=\"color:red\" for=\"d\">Onsdag</label>\n";
       webpage += "</div>\n";

        webpage += "<div class=\"col-md-1 col-sm-1\">\n";
                  if (day5[0] == '1')
                  {
                    webpage += "<input id=\"6\" onchange=\"saveData(this)\" type=\"checkbox\" checked>\n";
                  }
                  else
                  {
                    webpage += "<input id=\"6\" onchange=\"saveData(this)\" type=\"checkbox\">\n";
                  }
                  webpage += "<label style=\"color:red\" for=\"e\">Torsdag</label>\n";
       webpage += "</div>\n";

        webpage += "<div class=\"col-md-1 col-sm-1\">\n";
                  if (day6[0] == '1')
                  {
                    webpage += "<input id=\"7\" onchange=\"saveData(this)\" type=\"checkbox\" checked>\n";
                  }
                  else
                  {
                    webpage += "<input id=\"7\" onchange=\"saveData(this)\" type=\"checkbox\">\n";
                  }
                  webpage += "<label style=\"color:red\" for=\"f\">Fredag</label>\n";
       webpage += "</div>\n";

        webpage += "<div class=\"col-md-1 col-sm-1\">\n";
                  if (day7[0] == '1')
                  {
                    webpage += "<input id=\"8\" onchange=\"saveData(this)\" type=\"checkbox\" checked>\n";
                  }
                  else
                  {
                    webpage += "<input id=\"8\" onchange=\"saveData(this)\" type=\"checkbox\">\n";
                  }
                  webpage += "<label style=\"color:red\" for=\"g\">L&ouml;rdag</label>\n";
       webpage += "</div>\n";
  webpage += "</div>\n";
webpage += "</div>\n";

  getFooter();

  server.send(200, "text/html", webpage);
}

void javascriptPortfolio() { // here you can add javascript to this page
  javaScript = "<script type=\"text/javascript\">\n";
  javaScript += "function saveData(ele){\n";
  
  javaScript += "var boolValue;\n";
  javaScript += "if(ele.checked == true)\n";
  javaScript += "{\n";
  javaScript += "boolValue = '1';\n";
  javaScript += "}\n";
  javaScript += "else\n";
  javaScript += "{\n";
  javaScript += "boolValue = '0';\n";
  javaScript += "}\n";


  
  javaScript += "req = new XMLHttpRequest();\n";
  javaScript += "url =\"http://" + IpAddress + "/PinValue\";\n";
  javaScript += "var data = {pin: ele.id, value: boolValue};\n";
  javaScript += "req.open(\"POST\", url);\n";
  javaScript += "req.send(JSON.stringify(data));\n";
  javaScript += "}\n";

  javaScript += "function saveTime(ele){\n";

  javaScript += "req = new XMLHttpRequest();\n";
  javaScript += "url =\"http://" + IpAddress + "/PinValue\";\n";
  javaScript += "var data = {pin: ele.id, value: ele.value};\n";
  javaScript += "req.open(\"POST\", url);\n";
  javaScript += "req.send(JSON.stringify(data));\n";
  javaScript += "}\n";

  javaScript += "</script>\n";
}
