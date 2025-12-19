/*
  Yarrboard

  Author: Zach Hoeken <hoeken@gmail.com>
  Website: https://github.com/hoeken/yarrboard
  License: GPLv3
*/

#include "YarrboardDebug.h"
#include "YarrboardConfig.h"
#include "esp_freertos_hooks.h"
#include <algorithm>

YarrboardPrint YBP;
StringPrint startupLogger;