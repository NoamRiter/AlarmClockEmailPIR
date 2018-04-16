void PinValue()
{
  String data = server.arg("plain");
  yield();
  StaticJsonBuffer<200> jBuffer;
  JsonObject& jObject = jBuffer.parseObject(data);
  int pinNumber = jObject["pin"];
  String value = jObject["value"];
  yield();
  Serial.println("");
  Serial.print("pinNumber: ");
  Serial.println(pinNumber);

  Serial.println("");

  Serial.print("value: ");
  Serial.println(value);

  switch ((int)pinNumber) {
    case 1:

      Serial.println("try to send email");
     // pirStatus = false;
      yield();
      if (greenLEDStatus)
      {
        greenLEDStatus = false;
      }
      else
      {
        greenLEDStatus = true;
      }
      yield();
      break;

    case 2:  //söndag
      day1[0] = value[0];

      Serial.print("test :");
      Serial.println(day1);

      saveJson();
      break;

    case 3: //måndag
      day2[0] = value[0];
      saveJson();
      break;

    case 4:  //tisdag
      day3[0] = value[0];
      saveJson();
      break;

    case 5:  //onsdag

      day4[0] = value[0];
      saveJson();
      break;

    case 6:  //torsdag

      day5[0] = value[0];
      saveJson();
      break;

    case 7: //fredag
      day6[0] = value[0];
      saveJson();
      break;

    case 8: //lördag
      day7[0] = value[0];
      saveJson();
      break;


    case 9: //Time

      // AlarmMin = value.substring(3);
      AlarmHour[0] = value[0];
      AlarmHour[1] = value[1];
      AlarmMin[0] = value[3];
      AlarmMin[1] = value[4];

      saveJson();
      break;


    default:
      //do nothing!
      break;
  }

}
