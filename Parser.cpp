#include "Environment.h"  // Assuming Environment and other necessary types are defined in this or other headers
#include "YispError.cpp"
#include <any>

using namespace types;
using namespace yisp_error;

// foward declaration
sExpr eval(sExpr& expr, Environment& env);


inline void ifLiteralListMark(List& list) {
  for (int i = 0; i < list.size(); i++) {
    if (isSymbol(list[i])) {
      Symbol symbol = toSymbol(list[i]);
      if (symbol == "\'" || symbol == "quote") {
        if (i + 1 >= list.size()) {
          throw YispRuntimeError("Quote or \' must be followed by an atom");
        }
        if (isList(list[i + 1])) {
          List& nextAtom = toListRef(list[i + 1]);
          nextAtom.setLiteral();
          //setRecursiveLiteral(nextAtom);
          list.erase(list.begin() + i);
        }
      }
    }
  }
}

inline sExpr evalSymbol(List& list, Environment& env) {
  throwBadArgCount("Symbol?", list, 2);
  if (!isSymbol(list[1])) return false;
  Symbol symbol = toSymbol(list[1]);

  return env.hasVar(symbol);
}
// Has to be moved out of DefaultExpr to not execute list
inline sExpr evalQuote(List& list) {
  return List(list.begin() + 1, list.end());
}
inline sExpr evalIfExpr(List& list, Environment& env) {
  throwBadArgCount("if", list, 4);
  sExpr test = eval(list[1], env);
  return isNil(test) ? eval(list[3], env) : eval(list[2], env);
}

inline sExpr evalCondExpr(List& list, Environment& env) {

  for (int i = 1; i < list.size(); i++) {
    List cond = toListRef(list[i]);
    sExpr test = eval(cond[0], env);

    if (!isNil(test)) {

      return eval(cond[1], env);
    }
  }
  throw YispRuntimeError("Undefined behavior no COND conditon was true");
}
inline sExpr evalSetExpr(List& list, Environment& env) {
  throwBadArgCount("set", list, 3);
  if (env.isGlobal() == false) {
    throw YispRuntimeError("SET must be used only in global scope");
  }

  Symbol name = toSymbol(list[1]);
  sExpr val = eval(list[2], env);

  env.define(name, val);
  return types::VOID; // this will return nothing (not nil)
}

inline std::any evalQuote(List& list, Environment& env) {
  throwBadArgCount("quote or \'", list, 2);
  return list[1];
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

inline sExpr evalProcedureCall(Symbol& symbol, List& list, Environment& env) {
  Callable proc = env.getFunc(symbol);
  List args(list.begin() + 1, list.end());
  List evaluatedArgs;
  // std::cout << "evaluating procedure call: " << symbol << types::stringifyOutput(args) << std::endl;
   // may want to add ' support later
  for (auto& arg : args) {
    sExpr atom = eval(arg, env);
    //   std::cout << "evaluating arg call: "  << types::stringifyOutput(atom) << std::endl;

    evaluatedArgs.push_back(atom);
  }

  sExpr res = proc(evaluatedArgs);

  //  std::cout << "evaluating procedure call result: " << types::stringifyOutput(res) << std::endl;


  return res;
}


inline sExpr evalList(List& list, Environment& env) {
  ifLiteralListMark(list);

  if (list.empty()) return list;
  if (isLiteralList(list)) return list;

  if (isSymbol(list[0]))
   {
  Symbol head = toSymbol(list[0]);
    if (head == "quote" || head == "'")
      return evalQuote(list, env);

    if (head == "if") {
      return evalIfExpr(list, env);
    }
    if (head == "cond") {
      return evalCondExpr(list, env);
    }
    if (head == "set") {
      return evalSetExpr(list, env);
    }
    if (head == "define") {
      return evalDefineExpr(list, env);
    }
    if (head == "Symbol?") {
      return evalSymbol(list, env);
    }
    if (env.hasFunc(head))
      return evalProcedureCall(head, list, env);
    if (env.hasVar(head))
      return env.getVar(head);

    throw std::runtime_error(head + " is not a function name; try using a symbol instead");
  }


  throw std::runtime_error("Should be unreachable");

}

inline sExpr eval(std::any& expr, Environment& env) {
  if (isQuoteLiteral(expr)) {
    Symbol symbol = toSymbol(expr);
    return Symbol(symbol.begin() + 1, symbol.end());
  }
  if (isLiteral(expr)) {
    return expr;
  }
  if (isSymbol(expr)) {
    Symbol symbol = toSymbol(expr);
    return env.getVar(symbol);
  }
  if (isList(expr)) {
    List list = toList(expr);
    return evalList(list, env);
  }

  throw std::runtime_error("Unknown expression type");
}


