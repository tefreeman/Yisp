#include "Scanner.h"
#include <sstream>
#include <string>
#include <vector>
#include <any>
#include <deque>
#include "Types.h"

using namespace types;

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

void Scanner::Tokenize(std::string text)
{
  replaceAll(text, "(", " ( ");
  replaceAll(text, ")", " ) ");

  std::string token;
  std::istringstream tokenStream(text);


  while (getline(tokenStream, token, ' ')) {
    tokens_.push_back(token);
  }

  removeEmpty(tokens_);
}

List Scanner::readFromTokens(std::deque<std::string>& tokens)
{
  if (tokens.size() == 0) {
    throw std::invalid_argument("Unexpected End of File");
  }

  Symbol token = tokens_.front();
  tokens.pop_front();

  if (token == "(") {
    List list;
    
    while (tokens_.front() != ")") {
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

