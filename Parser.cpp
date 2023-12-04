#include <any>
#include <stdexcept>
#include "Environment.h"  // Assuming Environment and other necessary types are defined in this or other headers

using namespace types;

inline Environment globalEnv;

std::any eval(const std::any& expr, Environment& env);

inline bool isNil(const std::any& expr) {
  return expr.type() == typeid(List) && std::any_cast<List>(expr).empty();
}

// Has to be moved out of DefaultExpr to not execute list
inline std::any evalQuote(const List& list) {
  if (list.size() != 2) {
    throw "quote takes exactly 1 argument";
  }
  return list[1]; // Return the quoted expression as is
}
inline std::any evalIfExpr(const List& list, Environment& env) {
  if (list.size() != 4) {
    throw std::runtime_error("if takes exactly 3 arguments");
  }
  std::any test = eval(list[1], env);
  return isNil(test) ? eval(list[3], env) : eval(list[2], env);
}

inline std::any evalSetExpr(const List& list, Environment& env) {
  if (list.size() != 3) {
    throw std::runtime_error("set! takes exactly 2 arguments");
  }
  Symbol name = std::any_cast<Symbol>(list[1]);
  std::any val = eval(list[2], env);
  
  env.define(name, val);
  return std::any();
}

inline void evalDefineExpr(const List& list, Environment& env) {
  if (list.size() != 4) {
    throw std::runtime_error("define takes exactly 3 arguments");
  }
  Symbol name = std::any_cast<Symbol>(list[1]);

  env.defineProcedure(name, list[2], list[3]);

}

inline std::any evalProcedureCall(const Symbol& symbol, const List& list, Environment& env) {
  std::any val = env.get(symbol);

  // It's a literal type -> return
  if (val.type() != typeid(Expr)) 
    return val;

  // It's a function -> call
  Expr proc = std::any_cast<Expr>(val);

  List args(list.begin() + 1, list.end());
  List evaluatedArgs;

  for (const auto& arg : args) {
    evaluatedArgs.push_back(eval(arg, env));
  }

  return proc(evaluatedArgs);

}

inline std::any eval(const std::any& expr, Environment& env) {
  if (expr.type() == typeid(Symbol)) {
    return env.get(std::any_cast<Symbol>(expr));
  }
  else if (expr.type() == typeid(Number)) {
    return expr;
  }
  else if (expr.type() == typeid(List)) {
    const List& list = std::any_cast<List>(expr);
    if (list.empty()) {
      return list;
    }

    if (list[0].type() == typeid(Symbol)) {
      const Symbol& symbol = std::any_cast<Symbol>(list[0]);
      
      if (symbol == "if") {
        return evalIfExpr(list, env);
      }
      else if (symbol == "set") {
        return evalSetExpr(list, env);
      }
      else if (symbol == "define") {
        evalDefineExpr(list, env);
        return std::any(); // this will return nothing
      }
      else if (symbol == "quote") {
        return evalQuote(list);
      }
      else {
        return evalProcedureCall(symbol, list, env);
      }
    }
  }
  throw std::runtime_error("Unknown expression type");
}
