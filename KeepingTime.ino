void ClockToScreen()
{
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font

  if (hour() < 10)
  {
    u8g2.drawStr(0, 10, "0");
    char buf[9];
    sprintf (buf, "%d", hour());
    u8g2.drawStr(6, 10, buf);
  }
  else
  {
    char buf[9];
    sprintf (buf, "%d", hour());
    u8g2.drawStr(0, 10, buf);
  }

  u8g2.drawStr(13, 8, ":");

  if (minute() < 10)
  {
    u8g2.drawStr(17, 10, "0");
    char buf[9];
    sprintf (buf, "%d", minute());
    u8g2.drawStr(23, 10, buf);
  }
  else
  {
    char buf[9];
    sprintf (buf, "%d", minute());
    u8g2.drawStr(17, 10, buf);
  }

  u8g2.drawStr(29, 8, ":");

  if (second() < 10)
  {
    u8g2.drawStr(33, 10, "0");
    char buf[9];
    sprintf (buf, "%d", second());
    u8g2.drawStr(39, 10, buf);
  }
  else
  {
    char buf[9];
    sprintf (buf, "%d", second());
    u8g2.drawStr(33, 10, buf);
  }


  if (showIP)
  {
     String t = WiFi.localIP().toString() + ":" + port;
     char b[t.length()];
     for (int i = 0; i < t.length(); ++i)
    {
      b[i] = t[i];
    }

    
   // String t = WiFi.localIP().toString();
   // char buf[15];
    //itoa (buf, "%d",  WiFi.localIP());
    u8g2.drawStr(0, 30, b);
  }

  u8g2.sendBuffer();
}

