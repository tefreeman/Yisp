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

  std::any flattenList(std::any& element);
  std::deque<std::string> Tokenize(std::string& text);
  List readMultipleExpressions(std::deque<std::string>& tokens);
  std::any flattenSingleElementVectors(List& list);
  List readFromTokens(std::deque<std::string>& tokens);

public:
  List parse(std::string text);
};

