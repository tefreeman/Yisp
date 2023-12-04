#pragma once
#include "Environment.h"
#include <unordered_map>
#include "Types.h"
#include "Error.cpp"

using namespace yisp_error;

namespace expr {
  
  std::any Add(List args)
  {
    throwIfArgsNotNumbers("-", args);
    double result = std::any_cast<double>(args[0]);
    for (int i = 1; i < args.size(); i++)
    {
      result -= std::any_cast<double>(args[i]);
    }
    return result;
  }

  std::any Sub(List args)
  {
    throwIfArgsNotNumbers("-", args);
    double result = std::any_cast<double>(args[0]);
    for (int i = 1; i < args.size(); i++)
    {
      result -= std::any_cast<double>(args[i]);
    }
    return result;
  }

  std::any Mul(List args)
  {
    throwIfArgsNotNumbers("*", args);
    double result = 1;
    for (auto arg : args)
    {
      result *= std::any_cast<double>(arg);
    }
    return result;
  }

  std::any Div(List args)
  {
    throwIfArgsNotNumbers("/", args);
    double result = std::any_cast<double>(args[0]);
    for (int i = 1; i < args.size(); i++)
    {
      result /= std::any_cast<double>(args[i]);
    }
    return result;
  }

  std::any Gt(List args)
  {
    throwIfArgsNotNumbers(">", args);
    double a = std::any_cast<double>(args[0]);
    bool eval = true;
    for (int i = 1; i < args.size(); i++)
    {
      double b = std::any_cast<double>(args[i]);

      if (!(a > b)) {
        return false;
      }
    }
    return eval;
  }
  std::any Gte(List args)
  {
    throwIfArgsNotNumbers(">=", args);
    double a = std::any_cast<double>(args[0]);
    bool eval = true;
    for (int i = 1; i < args.size(); i++)
    {
      double b = std::any_cast<double>(args[i]);

      if (!(a >= b)) {
        return false;
      }
    }
    return eval;
  }

  std::any Lt(List args)
  {
    throwIfArgsNotNumbers("<", args);
    double a = std::any_cast<double>(args[0]);
    double b;
    bool eval = true;
    for (int i = 1; i < args.size(); i++)
    {
      double b = std::any_cast<double>(args[i]);

      if (!(a < b)) {
        return false;
      }
    }
    return eval;
  }

  std::any Lte(List args)
  {
    throwIfArgsNotNumbers("<=", args);
    double a = std::any_cast<double>(args[0]);
    double b;
    bool eval = true;
    for (int i = 1; i < args.size(); i++)
    {
      double b = std::any_cast<double>(args[i]);

      if (!(a <= b)) {
        return false;
      }
    }
    return eval;
  }


  std::any Eq(List args)
  {
    throwIfArgsNotNumbers("= or ==", args);
    throwBadArgCount("=", args, 2);

    if (args[0].type() != args[1].type())
      return false;
    if(args[0].type() == typeid(Number))
      return std::any_cast<double>(args[0]) == std::any_cast<double>(args[1]);
    else if (args[0].type() == typeid(Symbol))
      return std::any_cast<Symbol>(args[0]) == std::any_cast<Symbol>(args[1]);
    else if (args[0].type() == typeid(List))
      return false;
    else
      throw "invalid type given to EQ:";
  }


  std::any Cons(List args)
  {

    if (args.size() != 2) {
      throw "too many arguments given to CONS:";
    }

    List list = std::any_cast<List>(args[1]);
    list.insert(list.begin(), args[0]);
    return list;
  }

  std::any Car(List args)
  {
    throwIfArgEmptyList("CAR", args);
    if (args.size() != 1) {
      throw "too many arguments given to CAR:";
    }
    List list = std::any_cast<List>(args[0]);
    return list[0];
  }

  std::any Cdr(List args)
  {
    throwIfArgEmptyList("CDR", args);
    if (args.size() != 1) {
      throw "too many arguments given to CDR:";
    }
    List list = std::any_cast<List>(args[0]);
    list.erase(list.begin());
    return list;
  }

  std::any isNull(List args)
  {
    if (args.size() == 0)
      return true;
    return false;
  }

  std::any isNumber(List args)
  {
    throwBadArgCount("NUMBER?", args, 1);
    return args[0].type() == typeid(Number);
  }

  std::any isList(List args)
  {
    return args[0].type() == typeid(List);
  }

  std::any isNullAnd(List args) {
    throwBadArgCount("NULL?:", args, 2);
    if (args[0].type() != typeid(List) && args[1].type() != typeid(List)) {
      return true;
    }
    if (args[0].type() == typeid(List) && args[1].type() != typeid(List)) {
      List arg0 = std::any_cast<List>(args[0]);
      return !(std::any_cast<bool>(isNull(arg0)));
    }
    if (args[0].type() != typeid(List) && args[1].type() == typeid(List)) {
          List arg1 = std::any_cast<List>(args[1]);
          return !(std::any_cast<bool>(isNull(arg1)));
    }

    List arg0 = std::any_cast<List>(args[0]);
    List arg1 = std::any_cast<List>(args[1]);

    return !(std::any_cast<bool>(isNull(arg0))) && !(std::any_cast<bool>(isNull(arg1)));
  }

  std::any isNullOr(List args) {
    throwBadArgCount("NULL?:", args, 2);
    if (args[0].type() != typeid(List) || args[1].type() != typeid(List)) {
      return true;
    }

    List arg0 = std::any_cast<List>(args[0]);
    List arg1 = std::any_cast<List>(args[1]);

    return !(std::any_cast<bool>(isNull(arg0))) || !(std::any_cast<bool>(isNull(arg1)));
  }

  const inline std::unordered_map<std::string, Expr> defaultExprs = std::unordered_map<std::string, Expr>() = {
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
    {"list?", isList},
    {"nil?", isNull},
    {"and?", isNullAnd},
    {"or?", isNullOr}
  };
}