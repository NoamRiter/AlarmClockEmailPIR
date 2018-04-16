void sendEmail(String message)
{
  Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
  String subject = "Your ESP has send you a message!";

  if (gsender->Subject(subject)->Send(Email, message)) {
    Serial.println("Message send.");
  } else {
    Serial.print("Error sending message: ");
    Serial.println(gsender->getError());
  }
}


void sendEmailActiv()
{
  String timeIs;
  switch (emailTobeSend[0]) {
    case 'A':
      // do nothing
      break;

    case 'B':

      if (hours < 10) {
        timeIs = "0" + hours;
      }
      else{
        timeIs=hours;
      }
      if(minutes < 10)
      {
        timeIs = timeIs+":0"+minutes;
      }
      else{
        timeIs = timeIs + ":" + minutes;
      }
      if(seconds < 10){
        timeIs = timeIs + ":0" + seconds;
      }else{
        timeIs = timeIs + ":" + seconds;
      }
      yield();
      sendEmail("Alarm have been triggered at: " + timeIs +"IP: " + IpAddress);
      yield();
      emailTobeSend[0] = 'A';
      saveJson();
      yield();
      break;

    default:
      //do nothing!
      break;
  }
}

