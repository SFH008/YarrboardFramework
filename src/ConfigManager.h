/*
 * Yarrboard Framework
 *
 * Copyright (c) 2025 Zach Hoeken <hoeken@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ConfigManager_h
#define ConfigManager_h

#include "YarrboardConfig.h"
#include "controllers/AuthController.h"
#include "etl/array.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <Preferences.h>

class YarrboardApp;

class ConfigManager
{
  public:
    Preferences preferences;
    bool is_first_boot;

    char wifi_ssid[YB_WIFI_SSID_LENGTH] = YB_DEFAULT_AP_SSID;
    char wifi_pass[YB_WIFI_PASSWORD_LENGTH] = YB_DEFAULT_AP_PASS;
    char wifi_mode[YB_WIFI_MODE_LENGTH] = YB_DEFAULT_AP_MODE;
    char local_hostname[YB_HOSTNAME_LENGTH] = YB_DEFAULT_HOSTNAME;
    char uuid[YB_UUID_LENGTH];

    char board_name[YB_BOARD_NAME_LENGTH] = YB_BOARD_NAME;
    char startup_melody[YB_BOARD_NAME_LENGTH] = YB_PIEZO_DEFAULT_MELODY;
    char admin_user[YB_USERNAME_LENGTH] = YB_DEFAULT_ADMIN_USER;
    char admin_pass[YB_PASSWORD_LENGTH] = YB_DEFAULT_ADMIN_PASS;
    char guest_user[YB_USERNAME_LENGTH] = YB_DEFAULT_GUEST_USER;
    char guest_pass[YB_PASSWORD_LENGTH] = YB_DEFAULT_GUEST_PASS;
    char mqtt_server[YB_MQTT_SERVER_LENGTH] = "";
    char mqtt_user[YB_USERNAME_LENGTH] = "";
    char mqtt_pass[YB_PASSWORD_LENGTH] = "";
    String mqtt_cert = "";
    unsigned int app_update_interval = YB_DEFAULT_APP_UPDATE_INTERVAL;
    bool app_enable_mfd = YB_DEFAULT_APP_ENABLE_MFD;
    bool app_enable_api = YB_DEFAULT_APP_ENABLE_API;
    bool app_enable_serial = YB_DEFAULT_APP_ENABLE_SERIAL;
    bool app_enable_ota = YB_DEFAULT_APP_ENABLE_OTA;
    bool app_enable_ssl = YB_DEFAULT_APP_ENABLE_SSL;
    bool app_enable_mqtt = YB_DEFAULT_APP_ENABLE_SSL;
    bool app_enable_ha_integration = YB_DEFAULT_APP_ENABLE_HA_INTEGRATION;
    bool app_use_hostname_as_mqtt_uuid = YB_DEFAULT_USE_HOSTNAME_AS_MQTT_UUID;
    UserRole app_default_role = YB_DEFAULT_APP_DEFAULT_ROLE;
    UserRole serial_role = YB_DEFAULT_APP_DEFAULT_ROLE;
    UserRole api_role = YB_DEFAULT_APP_DEFAULT_ROLE;
    String app_theme = "light";
    float globalBrightness = 1.0;

    String server_cert;
    String server_key;

    String firmware_manifest_url = "https://raw.githubusercontent.com/hoeken/yarrboard-firmware/main/firmware.json";

    ConfigManager(YarrboardApp& app);

    // Lifecycle
    bool setup();

    // Core Config Logic
    bool saveConfig(char* error, size_t len);
    bool loadConfigFromFile(const char* file, char* error, size_t len);

    // JSON Loading
    bool loadConfigFromJSON(JsonVariant config, char* error, size_t len);
    bool loadNetworkConfigFromJSON(JsonVariant config, char* error, size_t len);
    bool loadAppConfigFromJSON(JsonVariant config, char* error, size_t len);
    bool loadBoardConfigFromJSON(JsonVariant config, char* error, size_t len);

    // JSON Generation
    void generateFullConfig(JsonVariant output);
    void generateBoardConfig(JsonVariant output);
    void generateAppConfig(JsonVariant output);
    void generateNetworkConfig(JsonVariant output);

  private:
    YarrboardApp& _app;
};

#endif