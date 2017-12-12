/**
 * ArduinoSimpleLogging
 *
 * https://github.com/janLo/ArduinoSimpleLogging
 *
 * Copyright (c) 2017 Jan Losinski.
 * MIT License
 */

#ifndef ARDUINOLOGGING_H
#define ARDUINOLOGGING_H

#include <forward_list>

#include <Print.h>

class ArduinoSimpleLogging {
 public:
  enum Level {
    ERROR = 0x01,
    WARNING = (0x01 << 1),
    INFO = (0x01 << 2),
    DEBUG = (0x01 << 3)
  };

  class LogTarget : public Print {
   public:
    explicit LogTarget(const Level level) : _level(level) {}
    LogTarget(const LogTarget &) = delete;
    LogTarget(const LogTarget &&) = delete;

    size_t write(uint8_t) override;
    size_t write(const uint8_t *buffer, size_t size) override;

   private:
    Level _level;
  };

  static LogTarget debug;
  static LogTarget info;
  static LogTarget warning;
  static LogTarget error;

  size_t log(Level level, const uint8_t *buffer, size_t size);
  size_t log(Level level, uint8_t);

  void addHandler(Level level, Print &);
  void removeHandler(Print &);

  static String levelToString(Level level);
  static Level stringToLevel(const String &levelName);

 private:
  struct LogHandler {
    const uint8_t mask;
    Print &stream;

    static uint8_t makeMask(Level level);
    LogHandler(Level level, Print &stream)
        : mask(makeMask(level)), stream(stream) {}
  };

  std::forward_list<LogHandler> handlers;
};

extern ArduinoSimpleLogging Logger;

#endif  // ARDUINOLOGGING_H
