#pragma once
#include <unordered_map>
#include <any>
#include <string>
#include "Types.h"

using namespace types;
class Environment
{
private:
  std::unordered_map<std::string, Expr> values_;
  Environment* enclosing_;


public:
  std::any Get(Symbol name, List args);
 // void Define(const std::string& name, const std::any& value);
  Environment();
  //~Environment();
};

