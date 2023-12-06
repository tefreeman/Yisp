#pragma once
#include "Environment.h"
#include <unordered_map>
#include "Types.h"
#include "Error.cpp"

using namespace yisp_error;
using namespace types;


/* A Set of default Funcs that take a list of args and returns a vale
 * These functions are reachable via basicOpMap
 */
namespace basic_ops {
  
  std::any Add(List& args)
  {
    throwBadArgsLt("+", args, 1);
    throwIfArgsNotNumbers("+", args);
    double result =toNumber(args[0]);
    for (int i = 1; i < args.size(); i++)
    {
      result +=  toNumber(args[i]);
    }
    return result;
  }

  std::any Sub(List& args)
  {
    throwBadArgsLt("-", args, 1);
    throwIfArgsNotNumbers("-", args);
    double result = toNumber(args[0]);
    for (int i = 1; i < args.size(); i++)
    {
      result -=  toNumber(args[i]);
    }
    return result;
  }

  std::any Mul(List& args)
  {
    throwBadArgsLt("*", args, 1);
    throwIfArgsNotNumbers("*", args);
    double result = 1;
    for (int i = 1; i < args.size(); i++)
    {
      result *= toNumber(args[i]);
    }
    return result;
  }

  std::any Div(List& args)
  {
    throwBadArgsLt("/", args, 1);
    throwIfArgsNotNumbers("/", args);
    double result = toNumber(args[0]);
    for (int i = 1; i < args.size(); i++)
    {
      result /=  toNumber(args[i]);
    }
    return result;
  }

  std::any Gt(List& args)
  {
    throwBadArgsLt(">", args, 2);
    throwIfArgsNotNumbers(">", args);
    double a = toNumber(args[0]);
    bool eval = true;
    for (int i = 1; i < args.size(); i++)
    {
      double b =  toNumber(args[i]);

      if (!(a > b)) {
        return false;
      }
    }
    return eval;
  }
  std::any Gte(List& args)
  {
    throwBadArgsLt(">=", args, 2);
    throwIfArgsNotNumbers(">=", args);
    double a = toNumber(args[0]);
    bool eval = true;
    for (int i = 1; i < args.size(); i++)
    {
      double b =  toNumber(args[i]);

      if (!(a >= b)) {
        return false;
      }
    }
    return eval;
  }

  std::any Lt(List& args)
  {
    throwBadArgsLt("<", args, 2);
    throwIfArgsNotNumbers("<", args);
    double a = toNumber(args[0]);
    bool eval = true;
    for (int i = 1; i < args.size(); i++)
    {
      double b =  toNumber(args[i]);

      if (!(a < b)) {
        return false;
      }
    }
    return eval;
  }

  std::any Lte(List& args)
  {
    throwBadArgsLt("<=", args, 2);
    throwIfArgsNotNumbers("<=", args);
    double a = toNumber(args[0]);
    bool eval = true;
    for (int i = 1; i < args.size(); i++)
    {
      double b =  toNumber(args[i]);

      if (!(a <= b)) {
        return false;
      }
    }
    return eval;
  }


  std::any Eq(List& args)
  {
    throwBadArgCount("= or ==", args, 2);

    if (args[0].type() != args[1].type())
      return false;
    if(types::isNumber(args[0]))
      return (toNumber(args[0]) == toNumber(args[1]));
    else if (types::isLiteralStr(args[0]))
      return toSymbol(args[0]) == toSymbol(args[1]);
    else if (types::isSymbol(args[0]))
        return toSymbol(args[0]) == toSymbol(args[1]);
    else if (types::isList(args[0])) {
      return toList(args[0]).size() == toList(args[1]).size();
   }
    else
      throw YispRuntimeError("invalid type given to EQ:");
  }



  std::any Cons(List args)
  {
    throwBadArgCount("CONS", args, 2);
    // atomic senario 
    if (isList(args[1]))
    {
      List args1List = toList(args[1]);
      if (!args1List.isCons()) {
      args1List.push_front(args[0]);
      return args1List;
      }
    }

    List consCell;
    consCell.setAsConsCell(true);
    consCell.push_back(args[0]);
    consCell.push_back(args[1]);
    return consCell;
   
  }


  std::any Car(List args)
  {
    throwIfArgEmptyList("CAR", args);
    throwBadArgCount("CAR", args, 1);
    List arg0 = toList(args[0]);
   
    return arg0[0];
  }

  std::any Cdr(List args)
  {
    throwBadArgCount("CDR", args, 1);
   
    if(!isList(args[0]))
      return args[0];

    List arg0 = toList(args[0]);

    if (arg0.isCons()) return arg0[1];
    if (arg0.empty()) return List();

    arg0.erase(arg0.begin());

    if (arg0.empty()) return List();

    return arg0;
  }

  std::any isNil(List args)
  {
    throwBadArgCount("Nil?", args, 1);
    return types::isNil(args[0]);
  }

  std::any isNumber(List args)
  {
    throwBadArgCount("NUMBER?", args, 1);
    return args[0].type() == typeid(Number);
  }



  std::any isNullAnd(List args) {
    throwBadArgCount("AND?", args, 2);


    if (!isList(args[0]) && !isList(args[1])) {
      return true;
    }
    if (isList(args[0]) && !isList(args[1])) {
      List arg0 = toList(args[0]);
      return !(types::isNil(arg0));
    }

    if (!isList(args[0]) && isList(args[1])) {
      List arg1 = toList(args[1]);
      return !(types::isNil(arg1));
    }

    if (isList(args[0]) && isList(args[1])) {
      List arg0 = toList(args[0]);
      List arg1 = toList(args[1]);
      return !types::isNil(arg0) && !types::isNil(arg1);
    }
    
    throw YispRuntimeError("Interal parser failure at isNullAnd");
  }

  std::any isNullOr(List& args) {
    throwBadArgCount("OR?", args, 2);

    if (!isList(args[0]) || !isList(args[1])) {
      return true;
    }

    if (isList(args[0]) && isList(args[1])) {
      List arg0 = toList(args[0]);
      List arg1 = toList(args[1]);
      return !(types::isNil(arg0) && types::isNil(arg1));
    }

  }

  std::any isListExpr(List& args) {
    throwBadArgCount("LIST?", args, 1);
    if (isList(args[0]))
      return isList(args[0]);
    return false;
  }
  std::any isSymbol(List args) {
    throwBadArgCount("SYMBOL?", args, 1);
    return types::isSymbol(args[0]);
  }

  std::any isAtom(List args) {
    throwBadArgCount("ATOM?", args, 1);
    if (isList(args[0]))
      return !isList(args[0]);
    return true;
  }

  std::any getTrue(List args) {
    return true;
  }
  inline std::unordered_map<std::string, Expr> basicOpMap = std::unordered_map<std::string, Expr>() = {
    {"+",  Add},
    {"add", Add}, 
    {"-",  Sub},
    {"sub", Sub},
    {"*",  Mul},
    {"mult", Mul},
    {"/",  Div},
    {"div", Div},
    {">",  Gt},
    {"gt", Gt},
    {"<",  Lt},
    {"lt", Lt},
    {"=",  Eq},
    {"<=", Lte},
    {"lte", Lte},
    {"gte", Gte},
    {">=", Gte},
    {"=",  Eq},
    {"cons", Cons},
    {"car", Car},
    {"cdr", Cdr},
    {"number?" , isNumber},
    {"list?", isListExpr},
    {"nil?", isNil},
    {"and?", isNullAnd},
    {"or?", isNullOr},
    {"symbol?", isSymbol},
    {"atom?", isAtom},
    {"t", getTrue}
  };
}