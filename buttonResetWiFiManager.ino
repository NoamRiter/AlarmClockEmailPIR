void buttonResetWifiManager()
{
  resetWifi[0] = 'B';
  saveJson();
  ESP.reset();
}

