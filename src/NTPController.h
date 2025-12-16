/*
  Yarrboard

  Author: Zach Hoeken <hoeken@gmail.com>
  Website: https://github.com/hoeken/yarrboard
  License: GPLv3
*/

#ifndef YARR_NTP_H
#define YARR_NTP_H

#include "esp_sntp.h"
#include "time.h"
#include <Arduino.h>

class YarrboardApp;
class ConfigManager;

class NTPController
{
  public:
    NTPController(YarrboardApp& app, ConfigManager& config);

    void setup();
    void loop();

    bool isReady();

  private:
    YarrboardApp& _app;
    ConfigManager& _config;

    const char* ntpServer1 = "pool.ntp.org";
    const char* ntpServer2 = "time.nist.gov";
    const long gmtOffset_sec = 0;
    const int daylightOffset_sec = 0;
    bool ntp_is_ready = false;

    int64_t ntp_get_time();
    void printLocalTime();

    // --- THE CALLBACK TRAP ---
    // Libraries expecting C-style function pointers cannot take normal member functions.
    // We use a static instance pointer and static methods to bridge the gap.
    static NTPController* _instance;
    static void _timeAvailableCallbackStatic(struct timeval* t);
    void timeAvailableCallback(struct timeval* t);
};

#endif /* !YARR_NTP_H */