#include "Environment.h"
#include <unordered_map>
#include "DefaultExpr.h"
#include "Procedure.h"


using namespace expr;




std::any Environment::get(Symbol name)
{
  if (defaultExprs.find(name) != defaultExprs.end())
  {
    return defaultExprs.at(name);
  }

  else if (localVars.find(name) != localVars.end())
  {
    return localVars.at(name);
  }

  if (enclosing_ != nullptr)
  {
    return enclosing_->get(name);
  }

  throw "Undefined variable " + name;
}

void Environment::define(Symbol name, std::any value)
{
  localVars[name] = value;
}

void Environment::define(Symbol name, Expr func)
{
  localVars[name] = func;
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