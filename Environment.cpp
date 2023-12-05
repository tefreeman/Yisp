#include "Environment.h"
#include <unordered_map>
#include "DefaultExpr.h"
#include "Procedure.h"
#include "util.cpp"

using namespace expr;




bool Environment::isGlobal()
{
  return enclosing_ == nullptr;
}

std::any Environment::get(Symbol name)
{
  std::string lowerName = yisp_util::strToLower(name);

  // default expressions are case insensitive
  if (defaultExprs.find(lowerName) != defaultExprs.end())
    return defaultExprs.at(lowerName);
  else if (localVars.find(name) != localVars.end())
    return localVars.at(name);
  else if (enclosing_ != nullptr)    
    return enclosing_->get(name);


  throw YispRuntimeError("Undefined variable " + name);
}

bool Environment::isIn(Symbol name)
{
  std::string lowerName = yisp_util::strToLower(name);

  // default expressions are case insensitive
  if (defaultExprs.find(name) != defaultExprs.end()) 
    return true;
  else if (localVars.find(name) != localVars.end())
    return true;
  else if (enclosing_ != nullptr)
    return enclosing_->isIn(name);

  return false;
}

void Environment::define(Symbol name, std::any& value)
{
  localVars[name] = value;
}

void Environment::define( Symbol name, Expr& func)
{
  localVars[name] = func;
}

void Environment::defineProcedure(Symbol name, std::any args, std::any expr)
{
  std::shared_ptr<Procedure> procedure = std::make_shared< Procedure>(Procedure(args, expr, this));
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