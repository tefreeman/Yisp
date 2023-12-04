#include <any>
#include <stdexcept>
#include "Environment.h"  // Assuming Environment and other necessary types are defined in this or other headers
#include "Error.cpp"

using namespace types;
using namespace yisp_error;

// foward declaration
Atom eval(const Atom& expr, Environment& env);


inline Atom evalSymbol(const List& list, Environment& env) {
  throwBadArgCount("Symbol?", list, 2);
  if (!isSymbol(list[1])) return false;
  Symbol symbol = toSymbol(list[1]);

  return env.isIn(symbol);
}
// Has to be moved out of DefaultExpr to not execute list
inline Atom evalQuote(const List& list) {
  throwBadArgCount("quote", list, 2);
  return list[1]; // Return the quoted expression as is
}
inline Atom evalIfExpr(const List& list, Environment& env) {
  throwBadArgCount("if", list, 4);
  Atom test = eval(list[1], env);
  return isNil(test) ? eval(list[3], env) : eval(list[2], env);
}

inline Atom evalSetExpr(const List& list, Environment& env) {
  throwBadArgCount("set", list, 3);
  if (env.isGlobal() == false) {
    throw YispRuntimeError("SET must be used only in global scope");
  }

  Symbol name = toSymbol(list[1]);
  Atom val = eval(list[2], env);
  
  env.define(name, val);
  return types::VOID; // this will return nothing (not nil)
}

inline std::any evalDefineExpr(const List& list, Environment& env) {
  throwBadArgCount("define", list, 4);
  Symbol name = toSymbol(list[1]);

  if (listContainsSymbol(list[3], "set")) {
    throw YispRuntimeError("SET can only be used in global scope");
  }
    
  env.defineProcedure(name, list[2], list[3]);
  return types::VOID; // this will return nothing (not nil)
}

inline Atom evalProcedureCall(const Symbol& symbol, const List& list, Environment& env) {
  Atom val = env.get(symbol);

  // It's a literal type -> return
  if (!isExpr(val)) return val;


  // It's a function -> call
  throwBadArgCount("DEFINE: " + symbol, list, 3);

  Expr proc = toExpr(val);
  List args(list.begin() + 1, list.end());
  List evaluatedArgs;

  for (const auto& arg : args) {
    evaluatedArgs.push_back(eval(arg, env));
  }

  return proc(evaluatedArgs);
}

inline Atom eval(const std::any& expr, Environment& env) {

  if (isLiteral(expr)) {
    return expr;
  }
  else if (expr.type() == typeid(Symbol)) {
    return env.get(toSymbol(expr));
  }
  else if (expr.type() == typeid(List)) {
    const List& list = toList(expr);

    if (list.empty()) return list;

    if (list[0].type() == typeid(Symbol)) {
      const Symbol symbol = toSymbol(list[0]);
      
      if (symbol == "if") {
        return evalIfExpr(list, env);
      }
      else if (symbol == "set") {
        return evalSetExpr(list, env);
      }
      else if (symbol == "define") {
        return evalDefineExpr(list, env);
      }
      else if (symbol == "quote" || symbol == "'") {
        return evalQuote(list);
      }
      else if (symbol == "symbol?") {
        return evalSymbol(list, env);
      }
      else {
        return evalProcedureCall(symbol, list, env);
      }
    }
  }
  std::string message = "Undefined evaluated expression, " + atomToStr(expr);
  throw YispRuntimeError(message.c_str());
}
