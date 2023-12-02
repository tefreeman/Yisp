#include "Environment.h"
#include <unordered_map>
#include "DefaultExpr.h"

using namespace expr;

std::any Environment::Get(Symbol name, List args)
{
  if (values_.find(name) != values_.end())
  {
    return values_[name](args);
  }
  if (enclosing_ != nullptr)
  {
    return enclosing_->Get(name, args);
  }
  throw  "Undefined variable '" + name + "'.";
}


Environment::Environment()
{
  enclosing_ = nullptr;
  values_ = std::unordered_map<std::string, Expr>() = {
    {"+",  Add},
    {"-",  Sub},
    {"*",  Mul},
    {"/",  Div},
    {">",  Gt},
    {"<",  Lt},
    {"<=", Lte},
    {">=", Gte},
    {"=",  Eq},
    {"cons", Cons},
    {"car", Car},
    {"cdr", Cdr},
    {"number?" , isNumber},
    {"symbol?", isSymbol},
    {"list?", isList}
  };
}
