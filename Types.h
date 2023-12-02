#pragma once
#include <string>
#include <deque>
#include <any>
#include <vector>
#include <functional>

namespace types {
  typedef double Number;
  typedef std::string Symbol;
  typedef std::vector<std::any> List;
  typedef std::function<std::any(std::vector<std::any>)> Expr;
}