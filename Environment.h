#pragma once
#include <unordered_map>
#include <any>
#include <string>
#include "Types.h"


using namespace types;
class Environment
{
private:
   std::unordered_map<std::string, std::any> variableValues;
   std::unordered_map<std::string, Expr> exprValues;
  Environment* enclosing_;


public:
  Expr getExpr(Symbol name); // function lookup
  std::any getVar(Symbol name); // variable lookup

  void define(Symbol name, const std::any value);
  void define(Symbol name, const Expr);

  void defineProcedure(Symbol name, std::any args, std::any expr);
  Environment();
  Environment(Environment* enclosing);
  //~Environment();
};

