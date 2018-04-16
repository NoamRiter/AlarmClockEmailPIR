#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <EEPROM.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <TimeLib.h>
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson

#include <WiFiUdp.h>

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C


//define your default values here, if there are different values in config.json, they are overwritten.
//length should be max size + 1
char mqtt_server[40];
char emailTobeSend[1];
char resetWifi[1];
char day1[1]; //Söndag
char day2[1]; //Måndag
char day3[1]; //Tisdag
char day4[1]; //Onsdag
char day5[1]; //Torsdag
char day6[1]; //Fredag
char day7[1]; //Lördag


char AlarmMin[2];
char AlarmHour[2];

int AlarmMinToInt = 21;
int AlarmHourToInt = 9;

bool AlarmStatus = false;
int AlarmTriger = 0;
int light = 0;
//flag for saving data
bool shouldSaveConfig = false;

IPAddress timeServerIP; // time.nist.gov NTP server address
static const char ntpServerName[] = "time.nist.gov";

// NTP Servers:
//static const char ntpServerName[] = "us.pool.ntp.org";
//static const char ntpServerName[] = "time.nist.gov";
//static const char ntpServerName[] = "time-a.timefreq.bldrdoc.gov";
//static const char ntpServerName[] = "time-b.timefreq.bldrdoc.gov";
//static const char ntpServerName[] = "time-c.timefreq.bldrdoc.gov";

const int timeZone = 1;     // Central European Time
//const int timeZone = -5;  // Eastern Standard Time (USA)
//const int timeZone = -4;  // Eastern Daylight Time (USA)
//const int timeZone = -8;  // Pacific Standard Time (USA)
//const int timeZone = -7;  // Pacific Daylight Time (USA)

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;
unsigned int localPort = 2390;      // local port to listen for UDP packets

int seconds = 0;
int minutes = 33;
int hours = 12;
int alarmOfTime = 70;


bool onOff = true; //alarm on/off

unsigned long timeNow = 0;
unsigned long timeLast = 0;
int secondsLast = 0;

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}


String webSite, javaScript, XML;



String passw = "z";
bool rightPassword = false;
String webYear = "2017";
String refreshPage = "60";
String mainHeading   = "Noam PIR";
String subHeading    = "Alarm system!";
String menuName = "Alarm";
String title     = "Esp8266 by Noam";
String copyrights = "Noams Art";
String webpage       = ""; //init webpage
String Email = "";
int port = 80; // Change the port to the one you open
String PublicIpAddress = "0"; //change it to your public IP. Open a rout/port on your ESP in router (TCP/UDP), Change the port to the one you open
String IpAddress = "0";
int openWifiManager;

int counterButton = 0;
int offcount = 0;
// pin list
const int pirSensor = D7;
const int resetButton = D8;
const int AlarmBTN = D0;
bool pirStatus = false;

const int greenLED = D6;
bool greenLEDStatus = true;
const int LEDPin = D5;
// bool pin2Status = true;
const int IPPin = D4;
const int PiezoPin = D3;

bool isEmail = false;
bool showIP = false;
int showIPShowTime = 0;

time_t getNtpTime();
void digitalClockDisplay();
void printDigits(int digits);
void sendNTPpacket(IPAddress &address);

ESP8266WebServer server(port);

void setup() {
  // put your setup code here, to run once:

  pinMode(pirSensor, INPUT);
  pinMode(resetButton, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(AlarmBTN , INPUT);
  pinMode(IPPin, INPUT);


  // pinMode(pin3, OUTPUT);
  // pinMode(pin4, OUTPUT);

  digitalWrite(greenLED, LOW);
  // digitalWrite(pin2, HIGH);
  // digitalWrite(pin3, HIGH);
  // digitalWrite(pin4, HIGH);


  Serial.begin(115200);
  u8g2.begin();

  Serial.println();

  //clean FS, for testing
  //SPIFFS.format();

  //read configuration from FS json
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");

          strcpy(mqtt_server, json["mqtt_server"]);
          strcpy(emailTobeSend, json["emailTobeSend"]);

          strcpy(resetWifi, json["resetWifi"]);

          strcpy(day1, json["day1"]);
          strcpy(day2, json["day2"]);
          strcpy(day3, json["day3"]);
          strcpy(day4, json["day3"]);
          strcpy(day5, json["day5"]);
          strcpy(day6, json["day6"]);
          strcpy(day7, json["day7"]);

          strcpy(AlarmMin, json["AlarmMin"]);
          strcpy(AlarmHour, json["AlarmHour"]);

        }
        else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read

  // The extra parameters to be configured (can be either global or just in the setup)
  // After connecting, parameter.getValue() will get you the configured value
  // id/name placeholder/prompt default length
  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);


  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);



  //add all your parameters here
  wifiManager.addParameter(&custom_mqtt_server);


  //reset settings - for testing
  //wifiManager.resetSettings();
  /*
    switch (resetWifi[0]) {
    case 'A':
      Serial.print("no resetWifi");

      // do nothing
      break;

    case 'B':
      yield();
      Serial.print("wifireset now");
      wifiManager.resetSettings();
      yield();
      resetWifi[0] = 'A';
      saveJson();
      yield();
      break;

    default:
      //do nothing!
      break;
    }
  */
  //set minimu quality of signal so it ignores AP's under that quality
  //defaults to 8%
  wifiManager.setMinimumSignalQuality();

  //sets timeout until configuration portal gets turned off
  //useful to make it all retry or go to sleep
  //in seconds
  //wifiManager.setTimeout(120);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration

  EEPROM.begin(500);
  openWifiManager = EEPROM.read(35);
  isEmail = EEPROM.read(35);
  Serial.println(openWifiManager);

  if (openWifiManager == 1)
  {
    wifiManager.resetSettings();
    EEPROM.write(35, 0);
    EEPROM.commit();
  }

  if (!wifiManager.autoConnect("Noams ESP", "password")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected......");

  //read updated parameters
  strcpy(mqtt_server, custom_mqtt_server.getValue());

  //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["mqtt_server"] = mqtt_server;
    json["emailTobeSend"] = emailTobeSend;
    json["resetWifi"] = resetWifi;
    //json["sunday"] = day1;
    //json["monday"] = day2;
    //json["tuesday"] = day3;
    //json["wednesday"] = day4;
    // json["thursday"] = day5;
    // json["freday"] = day6;
    // json["saturday"] = day7;


    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.prettyPrintTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
  }

  IpAddress = WiFi.localIP().toString();

  for (int index = 0; index < sizeof(mqtt_server) - 1; index++)
  {
    if (mqtt_server[index] != '\0' && mqtt_server[index] != ' ')
    {
      Email += mqtt_server[index];
    }
  }


  Email.trim();

  if (isEmail)
  {
    /*
      yield();
      sendEmail(WiFi.localIP().toString());
      yield();
      isEmail = false;
      EEPROM.write(40, 0);
      EEPROM.commit();
    */
  }

  Serial.print("");
  Serial.print("local ip: ");
  Serial.println(IpAddress);
  server.begin();



  /*
    switch (resetWifi[0]) {
      case 'A':
        Serial.print("no resetWifi");

        // do nothing
        break;

      case 'B':
        yield();
        Serial.print("wifireset now");
        resetWifi[0] = 'A';
        saveJson();
        wifiManager.resetSettings();
        yield();
        break;

      default:
        //do nothing!
        break;
    }
  */

  //Serial.print(resetWifi);


  server.on("/",         Product); // IP/
  server.on("/homepage", homepage);   // IP/homepage
  server.on("/Product", Product);      // IP/Product
  server.on("/Portfolio", Portfolio);      // IP/Portfolio
  server.on("/Services", Services);      // IP/Services
  server.on("/Aboutus", Aboutus);      // IP/Aboutus
  server.on("/Contact", Contact);      // IP/Contact
  server.on("/RestartWifiManager", RestartWifiManager);     //IP/RestartWifiManager
  server.on("/PinValue", PinValue);  //IP/PinValue
  server.on("/Password", Password);  //IP/PasswordValue


  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(Udp.localPort());
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);
  setSyncInterval(300);

  // sendEmailActiv();
}

time_t prevDisplay = 0; // when the digital clock was displayed

void loop() {

  server.handleClient();
  /*
    if (digitalRead(pirSensor) == LOW)
    {
      Serial.println("pir off");
      digitalWrite(greenLED, LOW);
      pirStatus = true;
    }

    if (digitalRead(pirSensor) == HIGH)
    {
      digitalWrite(greenLED, HIGH);
      Serial.println("pir on");
      //   emailTobeSend[0] = 'B';
      //  saveJson();
      //  sendEmailActiv();
      pirStatus = false;
      //  counterButton = 0;
    }
  */
int ccdc = digitalRead(pirSensor);
  if ( ccdc == 0 && pirStatus == false)
  {
    Serial.println("pir offffff");
    digitalWrite(greenLED, LOW);
    pirStatus = true;
    Serial.print("pirStatus: ");
    Serial.println(pirStatus);
    Serial.print("pir read: ");
    Serial.println(digitalRead(pirSensor));
  }
  else if (ccdc == 1 && pirStatus == true)
  {
    Serial.println("pir on");
    digitalWrite(greenLED, HIGH);
    pirStatus = false;
    Serial.print("pirStatus: ");
    Serial.println(pirStatus);
    Serial.print("pir read: ");
    Serial.println(digitalRead(pirSensor));
  }




  if (digitalRead(resetButton) == HIGH)
  {
    while (counterButton < 1) {
      Serial.println("digitalread wifi button");
      buttonResetWifiManager();
      counterButton++;
    }
  }
  else
  {
    counterButton = 0;
  }

  if (digitalRead(IPPin))
  {
    while (digitalRead(IPPin) == HIGH)
    {
    }
    showIP = true;
  }

  if (showIPShowTime >= 50 && showIP == true)
  {
    showIP = false;
    showIPShowTime = 0;
  }



  if (timeStatus() != timeNotSet) {
    if (now() != prevDisplay) { //update the display only if time has changed
      prevDisplay = now();
      ClockToScreen();
      alarmOfTime++;
      showIPShowTime++;
      if (light >= 1)
      {
        light++;
      }
    }
  }

  AlarmTriger = digitalRead(AlarmBTN);

  if (AlarmTriger == HIGH)
  {
    if (offcount == 3)
    {
      light = 0;
      alarmOfTime = 0;
      AlarmStatus = false;
      analogWrite(LEDPin, 0);
    }
    offcount++;
  }
  else
  {
    offcount = 0;
  }

  if (light < 255 && light >= 1 && alarmOfTime >= 65)
  {
    analogWrite(LEDPin, light);
  }


  if (AlarmHourToInt == (int)hour() && AlarmMinToInt == (int)minute() && AlarmStatus == false && alarmOfTime >= 65)
  {
    switch (weekday()) {
      case 1: //söndag
        if (day1[0] == '1')
        {
          light = 1;
          AlarmStatus = true;
        }
        break;

      case 2:  //måndag
        if (day2[0] == '1')
        {
          light = 1;
          AlarmStatus = true;
        }
        break;

      case 3: //tisdag
        if (day3[0] == '1')
        {
          light = 1;
          AlarmStatus = true;
        }
        break;

      case 4:   //onsdag
        if (day4[0] == '1')
        {
          light = 1;
          AlarmStatus = true;
        }
        break;

      case 5: //torsdag
        if (day5[0] == '1')
        {
          light = 1;
          AlarmStatus = true;
        }

        break;

      case 6:  //fredag
        if (day6[0] == '1')
        {
          light = 1;
          AlarmStatus = true;
        }

        break;

      case 7: //Lördag
        if (day7[0] == '1')
        {
          light = 1;
          AlarmStatus = true;
        }
        break;

      default:
        //do nothing!
        break;
    }
  }


}
