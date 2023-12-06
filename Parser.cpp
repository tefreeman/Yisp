#include <any>
#include <stdexcept>
#include "Environment.h"  // Assuming Environment and other necessary types are defined in this or other headers
#include "Error.cpp"

using namespace types;
using namespace yisp_error;

// foward declaration
Atom eval(Atom& expr, Environment& env);

inline void setRecursiveLiteral(List& list) {
  for (int i = 0; i < list.size(); i++) {
    if (isList(list[i])) {
      List& nextAtom = toListRef(list[i]);
      nextAtom.setLiteral();
      setRecursiveLiteral(nextAtom);
    }
  }
}

inline void evalLiteral(List& list) {
  for(int i = 0; i < list.size(); i++) {
    if (isSymbol(list[i])) {
      Symbol symbol = toSymbol(list[i]);
      if (symbol == "\'" || symbol == "quote") {
        if (i + 1 >= list.size()) {
                  throw YispRuntimeError("Quote or \' must be followed by an atom");
        }
        if (isList(list[i + 1])) {
          List& nextAtom = toListRef(list[i + 1]);
          nextAtom.setLiteral();
          setRecursiveLiteral(nextAtom);
          list.erase(list.begin() + i);
        }
      }
    }
  }
}

inline Atom evalSymbol(List& list, Environment& env) {
  throwBadArgCount("Symbol?", list, 2);
  if (!isSymbol(list[1])) return false;
  Symbol symbol = toSymbol(list[1]);

  return env.hasVar(symbol);
}
// Has to be moved out of DefaultExpr to not execute list
inline Atom evalQuote(List& list) {
  return List(list.begin() + 1, list.end());
}
inline Atom evalIfExpr(List& list, Environment& env) {
  throwBadArgCount("if", list, 4);
  Atom test = eval(list[1], env);
  return isNil(test) ? eval(list[3], env) : eval(list[2], env);
}

inline Atom evalCondExpr(List& list, Environment& env) {

  for (int i = 1; i < list.size(); i++) {
    List cond = toListRef(list[i]);
    Atom test = eval(cond[0], env);

    if (!isNil(test)) {

      return eval(cond[1], env);
    }
  }
  throw YispRuntimeError("Undefined behavior no COND conditon was true");
}
inline Atom evalSetExpr(List& list, Environment& env) {
  throwBadArgCount("set", list, 3);
  if (env.isGlobal() == false) {
    throw YispRuntimeError("SET must be used only in global scope");
  }

  Symbol name = toSymbol(list[1]);
  Atom val = eval(list[2], env);
  
  env.define(name, val);
  return types::VOID; // this will return nothing (not nil)
}

inline std::any evalDefineExpr(List& list, Environment& env) {
  throwBadArgCount("define", list, 4);
  Symbol name = toSymbol(list[1]);

  if (listContainsSymbol(list[3], "set")) {
    throw YispRuntimeError("SET can only be used in global scope");
  }
    
  env.defineProcedure(name, list[2], list[3]);
  return types::VOID; // this will return nothing (not nil)
}

inline Atom evalProcedureCall(Symbol& symbol, List& list, Environment& env) {
  Expr proc = env.getFunc(symbol);
  List args(list.begin() + 1, list.end());
  List evaluatedArgs;
 // std::cout << "evaluating procedure call: " << symbol << types::stringifyOutput(args) << std::endl;
  // may want to add ' support later
  for (auto& arg : args) {
    Atom atom = eval(arg, env);
//   std::cout << "evaluating arg call: "  << types::stringifyOutput(atom) << std::endl;

    evaluatedArgs.push_back(atom);
  }

  Atom res =  proc(evaluatedArgs);

//  std::cout << "evaluating procedure call result: " << types::stringifyOutput(res) << std::endl;
  

  return res;
}

inline Atom eval(std::any& expr, Environment& env) {
 if (isQuoteLiteral(expr)) {
    Symbol symbol = toSymbol(expr);
    return Symbol(symbol.begin() + 1, symbol.end());
  }
  if (isLiteral(expr)) {
    return expr;
  }
  else if (isSymbol(expr)) {
  Symbol symbol = toSymbol(expr);
    return env.getVar(symbol);
  }
  else if (isList(expr)) {
    List list = toList(expr);

    evalLiteral(list);

    if (list.empty()) return list;

    if (isSymbol(list[0])) {
      Symbol symbol = toSymbol(list[0]);
      
      if (symbol == "if") {
        return evalIfExpr(list, env);
      }
      else if (symbol == "cond") {
        return evalCondExpr(list, env);
      }
      else if (symbol == "set") {
        return evalSetExpr(list, env);
      }
      else if (symbol == "define") {
        return evalDefineExpr(list, env);
      } 
      else if (symbol == "Symbol?") {
        return evalSymbol(list, env);
      }
      else {
          if (env.hasVar(symbol)) 
            return env.getVar(symbol);
        return evalProcedureCall(symbol, list, env);
      }
    }
  }
  std::string message = "Undefined evaluated expression, " + atomToStr(expr);
  throw YispRuntimeError(message);
}
