/*
  Yarrboard

  Author: Zach Hoeken <hoeken@gmail.com>
  Website: https://github.com/hoeken/yarrboard
  License: GPLv3
*/

#ifndef YARR_DEBUG_CONTROLLER_H
#define YARR_DEBUG_CONTROLLER_H

#include "controllers/BaseController.h"

class YarrboardApp;
class ConfigManager;

class DebugController : public BaseController
{
  public:
    DebugController(YarrboardApp& app);

    bool setup() override;

    void handleCrashMe(JsonVariantConst input, JsonVariant output);

    String getResetReason();
    bool checkCoreDump();
    bool saveCoreDumpToFile(const char* path);
    bool deleteCoreDump();
    void crashMeHard();
    bool hasCoredump() { return has_coredump; }

    static int vprintf(const char* fmt, va_list args);

  private:
    bool has_coredump = false;
};

#endif /* !YARR_DEBUG_CONTROLLER_H */