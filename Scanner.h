#pragma once
#include "Types.h"
#include <any>
#include <deque>
#include <string>

using namespace types;
class Scanner
{
private:
  std::deque<std::string> Tokenize(std::string& text);
  List readMultipleExpressions(std::deque<std::string>& tokens);
  std::any readFromTokens(std::deque<std::string>& tokens);

  void checkForUnbalancedParentheses(std::deque<std::string>& tokens);
  void checkStartsWithParentheses(std::deque<std::string>& tokens);


public:
  List parse(std::string text);
};

