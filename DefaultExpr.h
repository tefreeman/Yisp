#pragma once
#include "Environment.h"
#include <unordered_map>
#include "Types.h"

namespace expr {
  std::any Add(List args)
  {
    double result = 0;
    for (auto arg : args)
    {
      result += std::any_cast<double>(arg);
    }
    return result;
  }
  
  std::any Sub(List args)
  {
    double result = std::any_cast<double>(args[0]);
    for (int i = 1; i < args.size(); i++)
    {
      result -= std::any_cast<double>(args[i]);
    }
    return result;
  }

  std::any Mul(List args)
  {
    double result = 1;
    for (auto arg : args)
    {
      result *= std::any_cast<double>(arg);
    }
    return result;
  }

  std::any Div(List args)
  {
    double result = std::any_cast<double>(args[0]);
    for (int i = 1; i < args.size(); i++)
    {
      result /= std::any_cast<double>(args[i]);
    }
    return result;
  }

  std::any Gt(List args)
  {
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
    if (args.size() == 0 || args.size() > 2) {
      throw "too many arguments given to EQ:";
    }

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
    if (args.size() != 1) {
      throw "too many arguments given to CAR:";
    }
    List list = std::any_cast<List>(args[0]);
    return list[0];
  }

  std::any Cdr(List args)
  {
    if (args.size() != 1) {
      throw "too many arguments given to CDR:";
    }
    List list = std::any_cast<List>(args[0]);
    list.erase(list.begin());
    return list;
  }

  std::any isNumber(List args)
  {
    if (args.size() != 1) {
      throw "too many arguments given to NUMBER?:";
    }
    return args[0].type() == typeid(Number);
  }
  std::any isSymbol(List args)
  {
    if (args.size() != 1) {
      throw "too many arguments given to SYMBOL?:";
    }
    return args[0].type() == typeid(Symbol);
  }
  std::any isList(List args)
  {
    if (args.size() != 1) {
      throw "too many arguments given to LIST?:";
    }
    return args[0].type() == typeid(List);
  }
  std::any isNull(List args)
  {
    if (args.size() != 1) {
      throw "too many arguments given to NULL?:";
    }
    return args.size();
  }

  std::any isNullAnd(List args) {
    if (args.size() > 2) {
      throw "too many arguments given to NULL?:";
    }
    return args.size() == 2;
  }

  std::any isNullOr(List args) {
    if (args.size() > 2) {
      throw "too many arguments given to NULL?:";
    }
    return args.size() >= 1;
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
    {"symbol?", isSymbol},
    {"list?", isList}
  };
}