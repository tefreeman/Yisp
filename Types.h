#pragma once
#include <string>
#include <deque>
#include <any>
#include <vector>
#include <functional>
#include "Error.cpp"

namespace types {
  

  typedef double Number;
  typedef std::string Symbol;
  typedef std::any Atom; // Number or Symbol or List
  typedef std::vector<std::any> List; // List of atoms
  typedef std::function<std::any(std::vector<std::any>)> Expr; // Expression

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

  inline List toList(const Atom& atom) {
    return std::any_cast<List>(atom);
  }

  inline Expr toExpr(const Atom& atom) {
    return std::any_cast<Expr>(atom);
  }
 
  inline bool isSymbol(const Atom& atom) {
    return atom.type() == typeid(Symbol);
  }

  inline bool isNumber(const Atom& atom) {
    return atom.type() == typeid(Number);
  }

  inline bool isList(const Atom& atom) {
    return atom.type() == typeid(List);
  }

  inline bool isVoid(const Atom& atom) {
    return atom.has_value() == false;
  }

  inline bool isLiteral(const Atom& exp) {
    if (exp.type() == typeid(Number)) return true;

    else if (exp.type() == typeid(Symbol)) {
      Symbol symbol = std::any_cast<Symbol>(exp);
      return _isEncasedInQuotes(symbol);
    }
    return false;
  }
  inline bool isNil(const Atom& expr) {
    return expr.type() == typeid(List) && std::any_cast<List>(expr).empty();
  }

  inline bool isExpr(const Atom& atom) {
    return atom.type() == typeid(Expr);
  }

  inline std::string atomToStr(const Atom& atom) {
    if(atom.has_value() == false) {
    return ""; // hack to represent void
    }
    if (atom.type() == typeid(Number)) {
      return std::to_string(toNumber(atom));
    }
    else if (atom.type() == typeid(Symbol)) {
      return std::string(toSymbol(atom));
    }
    else if (atom.type() == typeid(bool)) {
      bool val =  toBool(atom);
      return val ? "T" : "()";
    }
    throw YispRuntimeError("atomToStr: Unknown type");
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
}