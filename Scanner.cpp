#include "Scanner.h"
#include <sstream>
#include <string>
#include <vector>
#include <any>
#include <deque>
#include "Types.h"
#include "Util.cpp"


using namespace types;


std::any Scanner::_flattenList(std::any& element) {
  // If the element is a List, flatten it
  if (element.type() == typeid(List)) {
    return flattenSingleElementVectors(std::any_cast<List&>(element));
  }
  // Otherwise, return the element as is
  return element;
}

std::any Scanner::flattenSingleElementVectors(List& list) {
  for (auto& element : list) {
    element = _flattenList(element);
  }

  // If the list has only one element, return that element
  if (list.size() == 1) {
    return list[0];
  }
  // Otherwise, return the list
  return list;
}


void Scanner::removeEmpty(std::deque<std::string>& tokens) {
  for (auto it = tokens.begin(); it != tokens.end();) {
    if (*it == "") {
      it = tokens.erase(it);
    }
    else {
      ++it;
    }
  }
}



std::deque<std::string> Scanner::Tokenize(std::string& text)
{
  // All characters to lowercase

  text = yisp_util::removeComment(text, ";");

  std::deque<std::string> tokens;

  yisp_util::strReplaceAll(text, "(", " ( ");
  yisp_util::strReplaceAll(text, ")", " ) ");

  std::string token;
  std::istringstream tokenStream(text);


  while (getline(tokenStream, token, ' ')) {
    tokens.push_back(token);
  }

  removeEmpty(tokens);

  return tokens;
}

List Scanner::readMultipleExpressions(std::deque<std::string>& tokens) {
  List expressions;
  while (!tokens.empty()) {
    expressions.push_back(readFromTokens(tokens));
  }
  return expressions;
}

List Scanner::readFromTokens(std::deque<std::string>& tokens)
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
    std::vector<std::any> result;

    if (yisp_util::isRealNumber(token)) {
      result.push_back(std::stod(token));
    }
    else {
      result.push_back(token);
    }
    return result;
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

void Scanner::checkStartsWithParentheses(std::deque<std::string>& tokens)
{
  if (tokens.front() != "(") {
    throw YispRuntimeError("Expression must start with a parentheses");
  }
}

List Scanner::parse(std::string text)
{
  std::deque<std::string> tokens = Tokenize(text);

  checkStartsWithParentheses(tokens);
  checkForUnbalancedParentheses(tokens);

  List list = readMultipleExpressions(tokens);
  std::any flattendList = flattenSingleElementVectors(list);

  List returnedList;


  for (auto& element : toList(flattendList)) {
    returnedList.push_back(element);
  }

  return returnedList;
}


