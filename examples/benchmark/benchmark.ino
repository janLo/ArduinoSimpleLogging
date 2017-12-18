/**
 * Example to demonstate the speed of ArduinoSimpleLogging
 *
 * https://github.com/janLo/ArduinoSimpleLogging
 *
 * Copyright (c) 2017 Puuu
 * MIT License
 */

#include <ArduinoSimpleLogging.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif

#define MSG "This is a test log message!"

const char msg[] = MSG;
const unsigned int repeats = 1000;

String msgString(MSG);

class PrintMock : public Print {
 public:
  unsigned calls;

  size_t write(uint8_t) override {
    calls++;
    return 1;
  }

  size_t write(const uint8_t *, size_t length) override {
    calls++;
    return length;
  }

} printMock;

void log_char(Print &logger) {
  for (unsigned int i = 0; i < repeats; i++) {
    logger.println(msg);
  }
}

void log_singlechar(Print &logger) {
  for (unsigned int i = 0; i < repeats; i++) {
    for (unsigned int c = 0; c < sizeof(msg)-1; c++) {
      logger.write((uint8_t)msg[c]);
    }
    logger.write((uint8_t)'\n');
  }
}

void log_progmem(Print &logger) {
  for (unsigned int i = 0; i < repeats; i++) {
    logger.println(F(MSG));
  }
}

void log_String(Print &logger) {
  for (unsigned int i = 0; i < repeats; i++) {
    logger.println(msgString);
  }
}

unsigned long measure_it(Print &logger, void (*func)(Print &)) {
  unsigned long start = micros();
  func(logger);
  unsigned long end = micros();
  return end - start;
}

void summarize(unsigned long duration) {
  Serial.print("duration ");
  Serial.print(duration * 1000 / repeats);
  Serial.print(" us, ");
  Serial.print(printMock.calls / repeats);
  Serial.println(" calls");
}

void log(Print &logger) {
  unsigned long duration;
  Serial.println("char string");
  printMock.calls = 0;
  duration = measure_it(logger, log_char);
  summarize(duration);

  Serial.println("single chars");
  printMock.calls = 0;
  duration = measure_it(logger, log_singlechar);
  summarize(duration);

  Serial.println("PROGMEM string");
  printMock.calls = 0;
  duration = measure_it(logger, log_progmem);
  summarize(duration);

  Serial.println("String object");
  printMock.calls = 0;
  duration = measure_it(logger, log_String);
  summarize(duration);
}

void setup() {
  Serial.begin(115200);

#ifdef ESP8266
  // disable wifi for benchmarking
  WiFi.mode(WIFI_OFF);
#endif

  delay(500);
  Serial.println();

  // No handler configured - no output
  Serial.println("------------------------");
  Serial.println("No Handler ...");
  log(Logger.debug);
  Serial.println("------------------------");
  Serial.println();

  // Handler for error, logging to debug
  Serial.println("------------------------");
  Serial.println("Handler for error, logging to debug ...");
  Logger.addHandler(Logger.ERROR, printMock);
  log(Logger.debug);
  Serial.println("------------------------");
  Serial.println();

  // Handler for debug, logging to debug
  Serial.println("------------------------");
  Serial.println("Handler for error, logging to error ...");
  log(Logger.error);
  Serial.println("------------------------");
  Serial.println();
}

void loop() {
  // do nothing
}