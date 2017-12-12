/**
 * Example to demonstate the usage of ArduinoSimpleLogging
 *
 * https://github.com/janLo/ArduinoSimpleLogging
 *
 * Copyright (c) 2017 Jan Losinski.
 * MIT License
 */

#include <ArduinoSimpleLogging.h>


void log() {
  Logger.debug.println("Level: debug");
  Logger.info.println("Level: info");
  Logger.warning.println("Level: warning");
  Logger.error.println("Level: error");
}

void setup() {
  Serial.begin(115200);

  delay(500);
  Serial.println();

  // No handler configured - no output
  Serial.println("------------------------");
  Serial.println("No Handler ...");
  log();
  Serial.println("------------------------");
  Serial.println();

  // Handler for error - only error output
  Serial.println("------------------------");
  Serial.println("Handler for error ...");
  Logger.addHandler(Logger.ERROR, Serial);
  log();
  Serial.println("------------------------");
  Serial.println();

  // Handler for warning - error & warning output
  Serial.println("------------------------");
  Serial.println("Handler for error ...");
  Logger.addHandler(Logger.WARNING, Serial);
  log();
  Serial.println("------------------------");
  Serial.println();

  // Handler for info - error, warning & info output
  Serial.println("------------------------");
  Serial.println("Handler for error ...");
  Logger.addHandler(Logger.INFO, Serial);
  log();
  Serial.println("------------------------");
  Serial.println();

  // logger for debug - error, warning, info & debug output
  Serial.println("------------------------");
  Serial.println("Handler for error ...");
  Logger.addHandler(Logger.DEBUG, Serial);
  log();
  Serial.println("------------------------");
  Serial.println();

  // remove handler - no output
  Serial.println("------------------------");
  Serial.println("Handler removed ...");
  Logger.removeHandler(Serial);
  log();
  Serial.println("------------------------");
}

void loop() {

}