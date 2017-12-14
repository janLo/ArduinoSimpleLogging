/**
 * ArduinoSimpleLogging
 *
 * https://github.com/janLo/ArduinoSimpleLogging
 *
 * Copyright (c) 2017 Jan Losinski.
 * MIT License
 */

#ifndef LINEBUFFERPROXY_H
#define LINEBUFFERPROXY_H

#include <Print.h>

template <int Buffsize, char Sep = '\n'>
class LineBufferProxy : public Print {
 public:
  LineBufferProxy() : position(0) {}

  size_t write(uint8_t byte) override {
    buffer[position] = byte;
    position++;

    if (position >= Buffsize || byte == Sep) {
      doFlush();
    }

    return 1;
  }
  size_t write(const uint8_t* incomming, size_t size) override {
    size_t start = 0;

    while (size > 0) {
      size_t fit = std::min(size, Buffsize - position);

      bool newline = false;
      for (size_t i = 0; i < fit; ++i) {
        buffer[position + i] = incomming[start + i];
        if (incomming[i + start] == Sep) {
          newline = true;
          fit = i + 1;
          break;
        }
      }

      position += fit;

      if (position >= Buffsize || newline) {
        doFlush();
      }

      start += fit;
      size -= fit;
    }

    return start;
  }

  virtual ~LineBufferProxy() = default;

 protected:
  size_t size() const { return position; }
  virtual void flush(const char* buff) = 0;

 private:
  void doFlush() {
    buffer[position] = '\0';
    flush(reinterpret_cast<char*>(buffer));
    position = 0;
  }

  uint8_t buffer[Buffsize + 1];
  size_t position;
};

#endif  // LINEBUFFERPROXY_H
