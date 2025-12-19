/*
  Yarrboard

  Author: Zach Hoeken <hoeken@gmail.com>
  Website: https://github.com/hoeken/yarrboard
  License: GPLv3
*/

#ifndef YARR_DEBUG_CONTROLLER_H
#define YARR_DEBUG_CONTROLLER_H

#include "IntervalTimer.h"
#include "controllers/BaseController.h"

class YarrboardApp;
class ConfigManager;

class DebugController : public BaseController
{
  public:
    DebugController(YarrboardApp& app);

    IntervalTimer it;

    bool setup() override;
    void generateStatsHook(JsonVariant output) override;

    void handleCrashMe(JsonVariantConst input, JsonVariant output);

    String getResetReason();
    bool checkCoreDump();
    bool saveCoreDumpToFile(const char* path);
    bool deleteCoreDump();
    bool hasCoredump() { return has_coredump; }

    static int vprintf(const char* fmt, va_list args);

  private:
    bool has_coredump = false;

    void crashMeHard();
};

#endif /* !YARR_DEBUG_CONTROLLER_H */