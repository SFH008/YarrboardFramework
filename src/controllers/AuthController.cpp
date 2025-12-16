/*
  Yarrboard

  Author: Zach Hoeken <hoeken@gmail.com>
  Website: https://github.com/hoeken/yarrboard
  License: GPLv3
*/

#include "controllers/AuthController.h"
#include "ConfigManager.h"
#include "YarrboardApp.h"
#include "YarrboardDebug.h"

AuthController::AuthController(YarrboardApp& app) : BaseController(app, "auth")
{
}

bool AuthController::setup()
{
  // init our authentication stuff
  for (byte i = 0; i < YB_CLIENT_LIMIT; i++) {
    authenticatedClients[i].socket = 0;
    authenticatedClients[i].role = _cfg.app_default_role;
  }
}

void AuthController::loop()
{
}

bool AuthController::logClientIn(PsychicWebSocketClient* client, UserRole role)
{
  // did we not find a spot?
  if (!addClientToAuthList(client, role)) {
    YBP.println("Error: could not add to auth list.");

    // i'm pretty sure this closes our connection
    close(client->socket());

    return false;
  }

  return true;
}

bool AuthController::isLoggedIn(JsonVariantConst input, byte mode, PsychicWebSocketClient* connection)
{
  // login only required for websockets.
  if (mode == YBP_MODE_WEBSOCKET)
    return isWebsocketClientLoggedIn(input, connection);
  else if (mode == YBP_MODE_HTTP)
    return isApiClientLoggedIn(input);
  else if (mode == YBP_MODE_SERIAL)
    return isSerialClientLoggedIn(input);
  else
    return false;
}

UserRole AuthController::getUserRole(JsonVariantConst input, byte mode, PsychicWebSocketClient* connection)
{
  // login only required for websockets.
  if (mode == YBP_MODE_WEBSOCKET)
    return getWebsocketRole(input, connection);
  else if (mode == YBP_MODE_HTTP)
    return _cfg.api_role;
  else if (mode == YBP_MODE_SERIAL)
    return _cfg.serial_role;
  else
    return _cfg.app_default_role;
}

bool AuthController::isWebsocketClientLoggedIn(JsonVariantConst doc, PsychicWebSocketClient* client)
{
  // are they in our auth array?
  for (byte i = 0; i < YB_CLIENT_LIMIT; i++)
    if (authenticatedClients[i].socket == client->socket())
      return true;

  return false;
}

UserRole AuthController::getWebsocketRole(JsonVariantConst doc, PsychicWebSocketClient* client)
{
  // are they in our auth array?
  for (byte i = 0; i < YB_CLIENT_LIMIT; i++)
    if (authenticatedClients[i].socket == client->socket())
      return authenticatedClients[i].role;

  return _cfg.app_default_role;
}

bool AuthController::checkLoginCredentials(JsonVariantConst doc, UserRole& role)
{
  if (!doc["user"].is<String>())
    return false;
  if (!doc["pass"].is<String>())
    return false;

  // init
  char myuser[YB_USERNAME_LENGTH];
  char mypass[YB_PASSWORD_LENGTH];
  strlcpy(myuser, doc["user"] | "", sizeof(myuser));
  strlcpy(mypass, doc["pass"] | "", sizeof(myuser));

  // morpheus... i'm in.
  if (!strcmp(_cfg.admin_user, myuser) && !strcmp(_cfg.admin_pass, mypass)) {
    role = ADMIN;
    return true;
  }

  if (!strcmp(_cfg.guest_user, myuser) && !strcmp(_cfg.guest_pass, mypass)) {
    role = GUEST;
    return true;
  }

  // default to fail then.
  role = _cfg.app_default_role;
  return false;
}

bool AuthController::isSerialClientLoggedIn(JsonVariantConst doc)
{
  if (_app.protocol.isSerialAuthenticated())
    return true;
  else
    return checkLoginCredentials(doc, _cfg.serial_role);
}

bool AuthController::isApiClientLoggedIn(JsonVariantConst doc)
{
  return checkLoginCredentials(doc, _cfg.api_role);
}

bool AuthController::addClientToAuthList(PsychicWebSocketClient* client, UserRole role)
{
  byte i;
  for (i = 0; i < YB_CLIENT_LIMIT; i++) {
    // did we find an empty slot?
    if (!authenticatedClients[i].socket) {
      authenticatedClients[i].socket = client->socket();
      authenticatedClients[i].role = role;
      break;
    }

    // are we already authenticated?
    if (authenticatedClients[i].socket == client->socket())
      break;
  }

  // did we not find a spot?
  if (i == YB_CLIENT_LIMIT) {
    return false;
    YBP.println("ERROR: max clients reached");
  } else
    return true;
}

void AuthController::removeClientFromAuthList(PsychicWebSocketClient* client)
{
  byte i;
  for (i = 0; i < YB_CLIENT_LIMIT; i++) {
    // did we find an empty slot?
    if (authenticatedClients[i].socket == client->socket()) {
      authenticatedClients[i].socket = 0;
      authenticatedClients[i].role = _cfg.app_default_role;
    }
  }
}