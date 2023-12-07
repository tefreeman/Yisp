#pragma once
#include <unordered_map>
#include <any>
#include <string>
#include "Types.h"


using namespace types;
class Environment
{
private:
  std::unordered_map<std::string, std::any> localVars{{"t", true}, {"T", true}};
  std::unordered_map<std::string, Callable> localFuncs;
  Environment* enclosing_;

public:
  bool isGlobal();
  //
  Callable getFunc(Symbol name); 
  std::any& getVar(Symbol name);
  bool hasVar(Symbol name);
  bool hasFunc(Symbol name);

  void define(Symbol name,  std::any& value);
  void define(Symbol name,  Callable&);
  void defineProcedure(Symbol name, std::any args, std::any expr);


  Environment();
  Environment(Environment* enclosing);
  //~Environment();
};

