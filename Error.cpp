#pragma once
#include <string>
#include <iostream>
#include <exception>
#include <any>
#include <vector>
#include "Types.h"



using namespace types;



inline void Error(std::string message) {
  std::cout << "Error: " << message << std::endl;

}

inline std::string getError(std::string message) {
    return "Error: " + message;

}

class YispRuntimeError : public std::exception {
private:
  std::string message_;

public:
  inline YispRuntimeError(const char* message) : std::exception(message) {

    message_ = message;
  };

  inline YispRuntimeError(std::string message) : std::exception(message.c_str()) {

    message_ = message;
  };

  inline void display() {
    Error(message_);
  }

  inline std::string get() {
    return getError(message_);
  }

  const char* what() const throw () {
    return "YispRuntimeError";
  }


};


namespace yisp_error {

  inline void throwBadArgCount(std::string name, const List& args, int c) {
    if (args.size() != c) {
      throw YispRuntimeError(name + " expects " + std::to_string(c) + " arguments, got " + std::to_string(args.size()));
    }
  }

  inline void throwBadArgsLt(std::string name, const List& args, int c) {
    if (args.size() < c) {
      throw YispRuntimeError(name + " expects atleast " + std::to_string(c) + " arguments, got " + std::to_string(args.size()));
    }
  }
  inline void throwIfArgsNotNumbers(std::string name, const List& args) {
    for (auto arg : args) {
      if (arg.type() != typeid(Number)) {
        throw YispRuntimeError(name + " expects all arguments to be numbers");
      }
    }
  }

  inline void throwIfArgEmptyList(std::string name, const List& args) {
    if (args.size() != 1) {
      throw YispRuntimeError(name + " expects 1 argument");
    }
    if (args[0].type() != typeid(List)) {
      throw YispRuntimeError(name + " expects argument to be a list");
    }
    if (toList(args[0]).size() == 0) {
      throw YispRuntimeError(name + " expects argument to be a non-empty list");
    }
  }
  };