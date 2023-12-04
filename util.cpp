#pragma once
#include <iostream>
#include <string>
#include <sstream>


namespace yisp_util {
  // trim from start (in place)
  inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
      return !std::isspace(ch);
      }));
  }

  // trim from end (in place)
  inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
      return !std::isspace(ch);
      }).base(), s.end());
  }
  static inline void trim(std::string& s) {
    rtrim(s);
    ltrim(s);
  }

  inline std::string getTextAfterChar(const std::string& str, const char c) {
    size_t charPos = str.find(c);
    if (charPos != std::string::npos) {
      // Add 1 to colonPos to start after the colon character
      return str.substr(charPos + 1);
    }
    else {
      // Return an empty string if no colon is found
      return "";
    }
  }

  inline std::string extractComment(const std::string& str, const std::string& commentType) {
    bool inQuotes = false;
    size_t length = str.length();
    size_t commentTypeLength = commentType.length();

    for (size_t i = 0; i < length; ++i) {
      // Toggle inQuotes when a quote is found
      if (str[i] == '\"') {
        inQuotes = !inQuotes;
      }

      // Check for commentType outside of quotes
      if (!inQuotes && i <= length - commentTypeLength) {
        bool match = true;
        for (size_t j = 0; j < commentTypeLength; ++j) {
          if (str[i + j] != commentType[j]) {
            match = false;
            break;
          }
        }
        if (match) {
          return str.substr(i + commentTypeLength);
        }
      }
    }
    return ""; // Return empty string if no comment is found
  }

#include <string>

  inline std::string removeComment(const std::string& str, const std::string& commentType) {
    bool inQuotes = false;
    size_t length = str.length();
    size_t commentTypeLength = commentType.length();

    for (size_t i = 0; i < length; ++i) {
      // Toggle inQuotes when a quote is found
      if (str[i] == '\"') {
        inQuotes = !inQuotes;
      }

      // Check for commentType outside of quotes
      if (!inQuotes && i <= length - commentTypeLength) {
        bool match = true;
        for (size_t j = 0; j < commentTypeLength; ++j) {
          if (str[i + j] != commentType[j]) {
            match = false;
            break;
          }
        }
        if (match) {
          // Return the string up to the start of the comment
          return str.substr(0, i);
        }
      }
    }

    // Return the original string if no comment is found
    return str;
  }



inline bool isRealNumber(const std::string& str) {
  std::istringstream iss(str);
  double d;
  char c;
  return iss >> d && !(iss >> c);
}

inline bool isInteger(const std::string& str) {
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


inline void strReplaceAll(std::string& str, const std::string& from, const std::string& to) {
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length(); // Handles case if 'to' is a substring of 'from'
  }
}
}

namespace ansi {
  template < class CharT, class Traits >
  constexpr
    std::basic_ostream< CharT, Traits >& reset(std::basic_ostream< CharT, Traits >& os)
  {
    return os << "\033[0m";
  }

  template < class CharT, class Traits >
  constexpr
    std::basic_ostream< CharT, Traits >& foreground_black(std::basic_ostream< CharT, Traits >& os)
  {
    return os << "\033[30m";
  }

  template < class CharT, class Traits >
  constexpr
    std::basic_ostream< CharT, Traits >& foreground_red(std::basic_ostream< CharT, Traits >& os)
  {
    return os << "\033[31m";
  }

  template < class CharT, class Traits >
  constexpr
    std::basic_ostream< CharT, Traits >& foreground_green(std::basic_ostream< CharT, Traits >& os)
  {
    return os << "\033[32m";
  }
} // ansi