#include "Scanner.h"
#include <sstream>
#include <string>
#include <vector>
#include <any>
#include <deque>
#include "Types.h"

using namespace types;


std::any Scanner::flattenList(std::any& element) {
  // If the element is a List, flatten it
  if (element.type() == typeid(List)) {
    return flattenSingleElementVectors(std::any_cast<List&>(element));
  }
  // Otherwise, return the element as is
  return element;
}

std::any Scanner::flattenSingleElementVectors(List& list) {
  for (auto& element : list) {
    element = flattenList(element);
  }

  // If the list has only one element, return that element
  if (list.size() == 1) {
    return list[0];
  }
  // Otherwise, return the list
  return list;
}


void replaceAll(std::string& str, const std::string& from, const std::string& to) {
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length(); // Handles case if 'to' is a substring of 'from'
  }
}

void removeEmpty(std::deque<std::string>& tokens) {
  for (auto it = tokens.begin(); it != tokens.end();) {
    if (*it == "") {
      it = tokens.erase(it);
    }
    else {
      ++it;
    }
  }
}

bool isRealNumber(const std::string& str) {
  std::istringstream iss(str);
  double d;
  char c;
  return iss >> d && !(iss >> c);
}

bool isInteger(const std::string& str) {
  std::istringstream iss(str);
  int num;
  char c;
  if (!(iss >> num)) {
    return false; // not an integer
  }
  if (iss >> c) {
    return false; // additional characters after integer
  }
  return true; // is an integer
}

std::deque<std::string> Scanner::Tokenize(std::string& text)
{
  // All characters to lowercase

  for (int i = 0; i < text.length(); i++)
    text[i] = tolower(text[i]);

  std::deque<std::string> tokens;

  replaceAll(text, "(", " ( ");
  replaceAll(text, ")", " ) ");

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
    throw std::invalid_argument("Unexpected End of File");
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
    throw std::invalid_argument("Unexpected )");
  }
  else {
    std::vector<std::any> result;
   // if (isInteger(token)) {
   //   result.push_back(std::stoi(token));
   // }
    if (isRealNumber(token)) {
      result.push_back(std::stod(token));
    }
    else {
      result.push_back(token);
    }
    return result;
  }
 
}

List Scanner::parse(std::string text)
{
  std::deque<std::string> tokens = Tokenize(text);
  List list = readMultipleExpressions(tokens);
  std::any flattendList = flattenSingleElementVectors(list);

  List returnedList;


  for (auto& element : std::any_cast<std::vector<std::any>>(flattendList)) {
    returnedList.push_back(element);
  }

  return returnedList;
}


