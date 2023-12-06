#pragma once
#include <string>
#include <deque>
#include <any>
#include <vector>
#include <functional>
#include <iterator>
#include "Container.h"

namespace types {

  typedef double Number;
  typedef std::string Symbol;
  typedef std::any Atom; // Number or Symbol or List
  typedef Container<std::any> List; // List of atoms
  typedef std::function<std::any(Container<std::any>&)> Expr; // Expression

  // a hack to represent void check if std::any is empty;
  inline static const Atom VOID = std::any();

  inline bool _isEncasedInQuotes(const std::string& str) {
    // Check if the string is at least 2 characters long and starts and ends with a quote
    if (str.length() >= 2 && str.front() == '"' && str.back() == '"') {
      // Check if the quotes are not escaped
      if ((str.length() == 2) || (str[1] != '\\' && str[str.length() - 2] != '\\')) {
        return true;
      }
    }
    return false;
  }

  inline Symbol toSymbol(const Atom& atom) {
    return std::any_cast<Symbol>(atom);
  }
  inline Number toNumber(const Atom& atom) {
    return std::any_cast<Number>(atom);
  }

  inline bool toBool(const Atom& atom) {
    return std::any_cast<bool>(atom);
  }

  inline List& toListRef(Atom& atom) {
    return std::any_cast<List&>(atom);
  }

  inline List toList(const Atom& atom) {
    return std::any_cast<List>(atom);
  }

  inline Expr toExpr(const Atom& atom) {
    return std::any_cast<Expr>(atom);
  }
  inline bool isNumber(const Atom& atom) {
    return atom.type() == typeid(Number);
  }
  inline bool isLiteralStr(const Atom atom) {
    if (atom.type() == typeid(Symbol)) {
    Symbol symbol = toSymbol(atom);
    return _isEncasedInQuotes(symbol);
    }
    return false;
  }

  inline bool isList(const Atom& atom) {
    return atom.type() == typeid(List);
  }

  inline bool isLiteralList(const Atom& atom) {
    if (isList(atom)) {
      List list = toList(atom);
      return list.isLiteral();
    }
    return false;
  }
  inline bool isLiteral(const Atom& exp) {
    if (isNumber(exp)) return true;
    else if (isLiteralStr(exp)) return true;
    else if (isLiteralList(exp)) return true;

    return false;
  }
  inline bool isSymbol(const Atom& atom) {
    if (atom.type() != typeid(Symbol)) return false;

    Symbol symbol = toSymbol(atom);
    return !isLiteralStr(symbol) && !isNumber(symbol) && !isLiteralList(symbol);
  }

  inline bool isVoid(const Atom& atom) {
    return atom.has_value() == false;
  }


  inline bool isQuoteLiteral(const Atom& exp) {
    if (isSymbol(exp)) {
      Symbol symbol = toSymbol(exp);
      return symbol[0] == '\'';
      }
    return false;
  }

  inline bool isBool(const Atom& atom) {
    return atom.type() == typeid(bool);
  }

  inline bool isNil(const Atom& expr) {
    if (isList(expr)) {
      auto l = toList(expr);
      return toList(expr).empty();
      }
    else if (isBool(expr))
      return toBool(expr) == false;
    return false;
  }

  inline bool isExpr(const Atom& atom) {
    return atom.type() == typeid(Expr);
  }

  inline bool isConsCell(const Atom& atom) {
    if (isList(atom)) {
      List list = toList(atom);
      return list.isCons();
    }
    return false;
  }

  inline std::string atomToStr(const Atom& atom) {
    if(atom.has_value() == false) {
    return ""; // hack to represent void
    }
    if (atom.type() == typeid(Number)) {
      return std::to_string(int(toNumber(atom)));
    }
    else if (atom.type() == typeid(Symbol)) {
      return std::string(toSymbol(atom));
    }
    else if (atom.type() == typeid(bool)) {
      bool val =  toBool(atom);
      return val ? "T" : "()";
    }
    throw YispRuntimeError("At atomToStr: Atom is not a number, symbol, or bool")
  }

  // Recursively searches for symbol
  inline bool listContainsSymbol(std::any atomOrList, const Symbol& findMe) {
    if (isSymbol(atomOrList)) {
      Symbol symbol = toSymbol(atomOrList);
      return symbol == findMe;
    }
    if (isList(atomOrList)) {
      List list = toList(atomOrList);

      for (const auto& symbol : list) {
        return listContainsSymbol(symbol, findMe);
      }
    }

    return false;

  }

 inline  std::string stringifyOutput(std::any exp) {
    if (isList(exp)) {
      List lst = toList(exp);

      // Check if the list is a cons cell
      if (isConsCell(exp)) {
        // Assuming a cons cell has exactly two elements
        if (lst.size() == 2)
          return "(" + stringifyOutput(lst[0]) + " . " + stringifyOutput(lst[1]) + ")";
        else
          return   "(" + stringifyOutput(lst[0]) + ")";
      }
      else {
        // Handle as a regular list
        std::string result = "(";
        for (size_t i = 0; i < lst.size(); ++i) {
          if (i > 0) {
            result += " ";
          }
          result += stringifyOutput(lst[i]);
        }
        result += ")";
        return result;
      }
    }
    else {
      // Handle non-list types
      return atomToStr(exp);
    }
  }

}


