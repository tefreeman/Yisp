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

public:
   std::deque<std::string> tokens_;
   void Tokenize(std::string text);

   List readFromTokens(std::deque<std::string>& tokens);
};

