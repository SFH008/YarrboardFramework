/*
  Yarrboard

  Author: Zach Hoeken <hoeken@gmail.com>
  Website: https://github.com/hoeken/yarrboard
  License: GPLv3
*/

#ifndef YARR_AUTH_H
#define YARR_AUTH_H

#include "YarrboardConfig.h"
#include <Arduino.h>
#include <PsychicHttp.h>
#include <WiFi.h>

class YarrboardApp;
class ConfigManager;

typedef enum {
  NOBODY,
  GUEST,
  ADMIN
} UserRole;

typedef struct {
    int socket;
    UserRole role;
} AuthenticatedClient;

class AuthController
{
  public:
    AuthController(YarrboardApp& app, ConfigManager& config);

    AuthenticatedClient authenticatedClients[YB_CLIENT_LIMIT];

    void setup();
    void loop();

    UserRole getUserRole(JsonVariantConst input, byte mode, PsychicWebSocketClient* connection);
    bool logClientIn(PsychicWebSocketClient* connection, UserRole role);
    bool isLoggedIn(JsonVariantConst input, byte mode, PsychicWebSocketClient* connection);
    void removeClientFromAuthList(PsychicWebSocketClient* connection);
    bool isApiClientLoggedIn(JsonVariantConst doc);

  private:
    YarrboardApp& _app;
    ConfigManager& _config;

    bool addClientToAuthList(PsychicWebSocketClient* connection, UserRole role);
    bool isWebsocketClientLoggedIn(JsonVariantConst input, PsychicWebSocketClient* connection);
    bool isSerialClientLoggedIn(JsonVariantConst input);
    bool checkLoginCredentials(JsonVariantConst doc, UserRole& role);
    UserRole getWebsocketRole(JsonVariantConst doc, PsychicWebSocketClient* connection);
};

#endif /* !YARR_AUTH_H */