void saveJson()
{
  Serial.println("saving config");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["mqtt_server"] = mqtt_server;
  json["emailTobeSend"] = emailTobeSend;
  json["resetWifi"] = 'A';
  json["day1"] = day1;
  json["day2"] = day2;
  json["day3"] = day3;
  json["day4"] = day4;
  json["day5"] = day5;
  json["day6"] = day6;
  json["day7"] = day7;

  json["AlarmMin"] = AlarmMin;
  json["AlarmHour"] = AlarmHour;
  convertHoursToINT();
  convertMinutesToINT();
  
  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("failed to open config file for writing");
  }
//json.printTo(Serial);
  json.prettyPrintTo(Serial);
  json.printTo(configFile);
  configFile.close();
  //end save
}

void convertHoursToINT()
{
  AlarmHourToInt = ((AlarmHour[0] - '0')*10) + (AlarmHour[1] - '0');
}

void convertMinutesToINT()
{
  AlarmMinToInt = ((AlarmMin[0] - '0')*10) + (AlarmMin[1] - '0');
}
