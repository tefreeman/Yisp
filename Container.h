#pragma once
#include <any>
#include <deque>
#include <functional>
#include <iterator>
#include <string>
#include <vector>


// Simple container class that wraps a std::vector
// adds a flag to mark it as a cons cell
// and adds a flag to mark it as a literal value
template <typename T>
class Container {
private:
  std::vector<T> vec;
  bool isConsCell;
  bool isLiteralval;

public:
  // Constructor
  Container() : isConsCell(false), isLiteralval(false) {}

  template <typename InputIterator>
  Container(InputIterator first, InputIterator last)
    : vec(first, last), isConsCell(false), isLiteralval(false) {}

  Container(size_t size, const T& value)
    : vec(size, value), isConsCell(false), isLiteralval(false) {}

  // Copy constructor
  Container(const Container& other)
    : vec(other.vec), isConsCell(other.isConsCell), isLiteralval(other.isLiteralval) {}

  // Setter to mark as cons cell
  void setAsConsCell(bool value) {
    isConsCell = value;
  }

  void setLiteral() {
    isLiteralval = true;
  }

  bool isLiteral() const {
    return isLiteralval;
  }

  T& car() {
    return vec.front();
  }

  T& cdr() {
    return vec.back();
  }
  // Getter to check if it's a cons cell
  bool isCons() const {
    return isConsCell;
  }
  void push_front(const T& value) {
    vec.insert(vec.begin(), value);
  }
  // Forwarding methods to the internal std::vector
  void push_back(const T& value) {
    vec.push_back(value);
  }

  T& operator[](size_t index) {
    return vec[index];
  }

  const T& operator[](size_t index) const {
    return vec[index];
  }

  bool empty() const {
    return vec.empty();
  }

  size_t size() const {
    return vec.size();
  }
  typename std::vector<T>::iterator begin() {
    return vec.begin();
  }

  typename std::vector<T>::const_iterator begin() const {
    return vec.begin();
  }

  typename std::vector<T>::iterator end() {
    return vec.end();
  }

  typename std::vector<T>::const_iterator end() const {
    return vec.end();
  }

  typename std::vector<T>::iterator erase(typename std::vector<T>::iterator position) {
    return vec.erase(position);
  }

  typename std::vector<T>::iterator erase(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last) {
    return vec.erase(first, last);
  }

  std::vector<T>& getVector() {
    return vec;
  }

  const std::vector<T>& getVector() const {
    return vec;
  }
};
