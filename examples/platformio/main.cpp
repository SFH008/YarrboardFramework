/*
  Yarrboard Framework Example

  This example code is in the Public Domain (or CC0 licensed, at your option.)

  Unless required by applicable law or agreed to in writing, this
  software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
  CONDITIONS OF ANY KIND, either express or implied.
*/

#include "controllers/NavicoController.h"
#include <Arduino.h>
#include <YarrboardFramework.h>

// generated at build by running "gulp" in the firmware directory.
#include "index.html.gz.h"
#include "logo.png.gz.h"

YarrboardApp yba;
NavicoController navico(yba);

void setup()
{
  yba.http.index_length = index_html_gz_len;
  yba.http.index_sha = index_html_gz_sha;
  yba.http.index_data = index_html_gz;

  yba.http.logo_length = logo_gz_len;
  yba.http.logo_sha = logo_gz_sha;
  yba.http.logo_data = logo_gz;

  yba.registerController(navico);
  yba.setup();
}

void loop()
{
  yba.loop();
}