#pragma once
#include <unordered_map>
#include <any>
#include <string>
#include "Types.h"


using namespace types;
class Environment
{
private:
  std::unordered_map<std::string, std::any> localVars;
  Environment* enclosing_;

public:
  bool isGlobal();
  std::any get(Symbol name); // variable % function lookup)
  bool isIn(Symbol name);
  void define(Symbol name,  std::any& value);
  void define(Symbol name,  Expr&);
  void defineProcedure(Symbol name, std::any args, std::any expr);


  Environment();
  Environment(Environment* enclosing);
  //~Environment();
};

