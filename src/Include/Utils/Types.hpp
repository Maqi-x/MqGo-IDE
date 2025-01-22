#pragma once

#include <exception>
#include <stdint.h>

typedef std::string string;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float float32;
typedef double float64;

class SysError : public std::exception {
  private:
    string msg;

  public:
    SysError(const std::string &message) : msg(message) {}

    const char *what() const noexcept override { return msg.c_str(); }
};