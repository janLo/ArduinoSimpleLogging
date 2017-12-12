/**
 * ArduinoSimpleLogging
 *
 * https://github.com/janLo/ArduinoSimpleLogging
 *
 * Copyright (c) 2017 Jan Losinski.
 * MIT License
 */

#include "ArduinoSimpleLogging.h"

size_t ArduinoSimpleLogging::LogTarget::write(uint8_t byte) {
  return Logger.log(_level, byte);
}

size_t ArduinoSimpleLogging::LogTarget::write(const uint8_t *buffer,
                                              size_t size) {
  return Logger.log(_level, buffer, size);
}

size_t ArduinoSimpleLogging::log(ArduinoSimpleLogging::Level level,
                                 const uint8_t *buffer, size_t size) {
  for (auto &handler : handlers) {
    if ((handler.mask & level) != 0) {
      handler.stream.write(buffer, size);
    }
  }
  return size;
}

size_t ArduinoSimpleLogging::log(ArduinoSimpleLogging::Level level,
                                 uint8_t byte) {
  for (auto &handler : handlers) {
    if ((handler.mask & level) != 0) {
      handler.stream.write(byte);
    }
  }

  return 1;
}

uint8_t ArduinoSimpleLogging::LogHandler::makeMask(
    const ArduinoSimpleLogging::Level level) {
  uint8_t mask = 0x0;
  while (mask < level) {
    mask = (mask << 1) | (uint8_t)0x01;
  }
  return mask;
}

void ArduinoSimpleLogging::addHandler(ArduinoSimpleLogging::Level level,
                                      Print &stream) {
  removeHandler(stream);
  handlers.emplace_front(level, stream);
}

void ArduinoSimpleLogging::removeHandler(Print &stream) {
  handlers.remove_if([&stream](const LogHandler &handler) {
    return &(handler.stream) == &stream;
  });
}

ArduinoSimpleLogging Logger;

ArduinoSimpleLogging::LogTarget ArduinoSimpleLogging::debug(DEBUG);
ArduinoSimpleLogging::LogTarget ArduinoSimpleLogging::info(INFO);
ArduinoSimpleLogging::LogTarget ArduinoSimpleLogging::warning(WARNING);
ArduinoSimpleLogging::LogTarget ArduinoSimpleLogging::error(ERROR);
