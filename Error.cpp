#pragma once
#include <string>
#include <iostream>
#include <exception>
#include <any>
#include <vector>



namespace yisp_error {
  typedef std::vector<std::any> List; //forward declartion from types.h
  typedef double Number;

inline void throwBadArgCount(std::string name, const List& args, int c) {
  if (args.size() != c) {
    throw name + " expects " + std::to_string(c) + " arguments, got " + std::to_string(args.size());
  }
}

inline void throwIfArgsNotNumbers(std::string name, const List& args) {
  for (auto arg : args) {
    if (arg.type() != typeid(Number)) {
      throw name + " expects all arguments to be numbers";
    }
  }
}

inline void throwIfArgEmptyList(std::string name, const List& args) {
  if (args.size() != 1) {
    throw name + " expects 1 argument";
  }
  if (args[0].type() != typeid(List)) {
    throw name + " expects argument to be a list";
  }
  if (std::any_cast<List>(args[0]).size() == 0) {
    throw name + " expects argument to be a non-empty list";
  }
}

}

inline void Error(const char* message) {
  std::cout << "Error: " << message << std::endl;

}

class YispRuntimeError : public std::exception {
private:
  const char* message_;

public:
  inline YispRuntimeError(const char* message) : std::exception(message) {

    message_ = message;
  };

  inline YispRuntimeError(std::string message) : std::exception(message.c_str()) {

    message_ = message.c_str();
  };

  inline void display() {
    Error(message_);
  }

  const char* what() const throw () {
    return "YispRuntimeError";
  }


};
