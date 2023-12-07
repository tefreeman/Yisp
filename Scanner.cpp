#include "YispError.cpp"
#include "Scanner.h"
#include "Types.h"
#include "Util.cpp"
#include <any>
#include <deque>
#include <sstream>
#include <string>
#include <vector>

using namespace types;

std::deque<std::string> Scanner::Tokenize(std::string& text)
{
  // Remove comments and replace parentheses with spaces
  text = yisp_util::removeComments(text, ";");
  yisp_util::strReplaceAll(text, "(", " ( ");
  yisp_util::strReplaceAll(text, ")", " ) ");

  std::deque<std::string> tokens;
  std::istringstream tokenStream(text);
  std::string token;
  bool inString = false;

  // Tokenize the string
  while (tokenStream >> std::noskipws) {
    char ch;
    tokenStream >> ch;
    if (ch == '\"') {
      if (!inString) {
        if (!token.empty()) {
          tokens.push_back(token);
          token.clear();
        }
        token += ch;
      }
      else {
        token += ch;
        tokens.push_back(token);
        token.clear();
      }
      inString = !inString;
    }
    else if (std::isspace(ch) && !inString) {
      if (!token.empty()) {
        tokens.push_back(token);
        token.clear();
      }
    }
    else {
      token += ch;
    }
  }

  if (!token.empty()) {
    tokens.push_back(token);
  }

  return tokens;
}

List Scanner::readMultipleExpressions(std::deque<std::string>& tokens) {
  List expressions;
  List tokenLine;

  while (!tokens.empty()) {
    
    // removes the ' if its the first token 
    bool doesStartWithQuote = firstTokenIsQuote(tokens);
    tokenLine = toList(readFromTokens(tokens));  // Read a single expression ( ... )
      
    // puts the ' back in

    if (!isList(tokenLine)) {
      List list = List();
      list.push_back(tokenLine);
      if (doesStartWithQuote) list.push_front(std::string("\'"));
      expressions.push_back(list);
    }
    else {
      if (doesStartWithQuote) tokenLine.push_front(std::string("\'"));
      expressions.push_back(tokenLine);
    }
  }
  return expressions;
}

std::any Scanner::readFromTokens(std::deque<std::string>& tokens)
{

  if (tokens.size() == 0) {
    throw YispRuntimeError("Unexpected End of File");
  }

  Symbol token = tokens.front();
  tokens.pop_front();
  if (token == "(") {
    List list;

    while (tokens.front() != ")") {
      list.push_back(readFromTokens(tokens));
    }
    tokens.pop_front();
    return list;
  }
  else if (token == ")") {
    throw YispRuntimeError("Unexpected )");
  }
  else {

    if (yisp_util::isRealNumber(token)) {
      return std::stod(token);
    }
    else {
      return (token);
    }
  }

}
void Scanner::checkForUnbalancedParentheses(std::deque<std::string>& tokens)
{
  int openParentheses = 0;
  int closedParentheses = 0;

  for (auto& token : tokens) {
    if (token == "(") {
      openParentheses++;
    }
    else if (token == ")") {
      closedParentheses++;
    }
  }

  if (openParentheses != closedParentheses) {
    throw YispRuntimeError("Unbalanced parentheses");
  }
}

void Scanner::checkStartsWithValidToken(std::deque<std::string>& tokens)
{
  if (tokens.front() != "(" && tokens.front() != "\'") {
    throw YispRuntimeError("Expression must start with a parentheses");
  }
}

bool Scanner::firstTokenIsQuote(std::deque<std::string>& tokens) {
  if (tokens.front() == "\'") {
    tokens.pop_front();
    return true;
  }
  return false;
}
List Scanner::parse(std::string text)
{
  std::deque<std::string> tokens = Tokenize(text);


  checkStartsWithValidToken(tokens);
  checkForUnbalancedParentheses(tokens);
  return readMultipleExpressions(tokens);

}
