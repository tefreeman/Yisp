#include "Environment.h"
#include <unordered_map>
#include "BasicOperations.h"
#include "Procedure.h"
#include "util.cpp"

using namespace basic_ops;

bool Environment::isGlobal()
{
  return enclosing_ == nullptr;
}

Callable Environment::getFunc(Symbol name)
{
  std::string lowerName = yisp_util::strToLower(name);
  // default expressions are case insensitive
  if (basicOpMap.find(lowerName) != basicOpMap.end())
    return basicOpMap.at(lowerName);


  else if (localFuncs.find(name) != localFuncs.end())
    return localFuncs.at(name);
  else if (enclosing_ != nullptr)    
    return enclosing_->getFunc(name);


  throw YispRuntimeError("Undefined function " + name);
}

std::any &Environment::getVar(Symbol name)
{
  if (localVars.find(name) != localVars.end())
    return localVars.at(name);
  else if (enclosing_ != nullptr)
    return enclosing_->getVar(name);

  throw YispRuntimeError("Undefined variable " + name);
}

bool Environment::hasVar(Symbol name)
{
  // default expressions are case insensitive
  if (localVars.find(name) != localVars.end())
    return true;
  else if (enclosing_ != nullptr)
    return enclosing_->hasVar(name);

  return false;
}

bool Environment::hasFunc(Symbol name)
{
  std::string lowerName = yisp_util::strToLower(name);

  // default expressions are case insensitive
  if (basicOpMap.find(lowerName) != basicOpMap.end())
    return true;
  else if (localFuncs.find(name) != localFuncs.end())
    return true;
  else if (enclosing_ != nullptr)
    return enclosing_->hasFunc(name);

  return false;
}

void Environment::define(Symbol name, std::any& value)
{
  localVars[name] = value;
}

void Environment::define( Symbol name, Callable& func)
{
  localFuncs[name] = func;
}

void Environment::defineProcedure(Symbol name, std::any args, std::any expr)
{
  std::shared_ptr<Procedure> procedure = std::make_shared< Procedure>(Procedure(args, expr, this));
  Callable boundFunction = std::bind(&Procedure::call, procedure, std::placeholders::_1);
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