#pragma once
#include <string>
#include <deque>
#include <any>
#include <vector>
#include "Types.h"

using namespace types;
class Scanner
{
private:

  std::any _flattenList(std::any& element);
  std::deque<std::string> Tokenize(std::string& text);
  List readMultipleExpressions(std::deque<std::string>& tokens);
  std::any flattenSingleElementVectors(List& list);
  void removeEmpty(std::deque<std::string>& tokens);
  std::any readFromTokens(std::deque<std::string>& tokens);

  void checkForUnbalancedParentheses(std::deque<std::string>& tokens);
  void checkStartsWithParentheses(std::deque<std::string>& tokens);


public:
  List parse(std::string text);
};

