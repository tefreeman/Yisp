#pragma once
#include "Types.h"

using namespace types;
namespace commands {

  enum class CmdTypes {
    VAR,
    LITERAL,
    DEFINE,
    SET,
    CONS,
    COND,
    CAR,
    CDR,
    IS_AND,
    IS_OR,
    IS_NOT,
    IS_NUMBER,
    IS_NIL,
    IS_EQ,
    PLUS,
    MINUS,
    MULTI,
    DIV,
    EQ,
    LT,
    GT,
    IF
  };



  inline CmdTypes getType(Symbol str) {
    
    for (int i = 0; i < str.length(); i++)
      str[i] = tolower(str[i]);

    if(str == "define") return CmdTypes::DEFINE;
    if(str == "set") return CmdTypes::SET;
    if(str == "cons") return CmdTypes::CONS;
    if(str == "cond") return CmdTypes::COND;
    if(str == "car") return CmdTypes::CAR;
    if(str == "cdr") return CmdTypes::CDR;
    if(str == "and") return CmdTypes::IS_AND;
    if(str == "or") return CmdTypes::IS_OR;
    if(str == "not") return CmdTypes::IS_NOT;
    if(str == "number?") return CmdTypes::IS_NUMBER;
    if(str == "nil?") return CmdTypes::IS_NIL;
    if(str == "eq?") return CmdTypes::IS_EQ;
    if(str == "+") return CmdTypes::PLUS;
    if(str == "-") return CmdTypes::MINUS;
    if(str == "*") return CmdTypes::MULTI;
    if(str == "/") return CmdTypes::DIV;
    if(str == "=" || str == "==") return CmdTypes::EQ;
    if(str == "<") return CmdTypes::LT;
    if(str == ">") return CmdTypes::GT;
    if(str == "if") return CmdTypes::IF;


  }
}