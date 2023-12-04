#include "Environment.h"
#include <unordered_map>
#include "DefaultExpr.h"
#include "Procedure.h"


using namespace expr;

Expr Environment::getExpr(Symbol name)
{
  if (defaultExprs.find(name) != defaultExprs.end())
  {
    return defaultExprs.at(name);
  }

  else if (exprValues.find(name) != exprValues.end())
  {
    return exprValues.at(name);
  }
  
  if (enclosing_ != nullptr)
  {
    return enclosing_->getExpr(name);
  }
  
  throw  "Undefined variable '" + name + "'.";
}

std::any Environment::getVar(Symbol name)
{
  if (variableValues.find(name) != variableValues.end())
  {
    return variableValues.at(name);
  }
  
  if (enclosing_ != nullptr)
  {
    return enclosing_->getVar(name);
  }
  
  throw  "Undefined variable '" + name + "'.";
}


void Environment::define(Symbol name, std::any value)
{
  variableValues[name] = value;
}

void Environment::define(Symbol name, Expr func)
{
  exprValues[name] = func;
}
void Environment::defineProcedure(Symbol name, std::any args, std::any expr)
{
  Procedure* procedure = new Procedure(args, expr, this);

  //procedures.push_back(procedure);

  Expr boundFunction = std::bind(&Procedure::call, procedure, std::placeholders::_1);

  define(name, boundFunction);
}

Environment::Environment()
{
  enclosing_ = nullptr;
}

Environment::Environment(Environment* enclosing)
{
  enclosing_ = enclosing;
}