#pragma once
#include <iostream>
#include <string>
#include <algorithm>
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
    size_t commentStart = str.find(commentType);
    if (commentStart != std::string::npos) {
      size_t endOfLine = str.find('\n', commentStart);
      if (endOfLine != std::string::npos) {
        // Extract and return the comment, up to the newline character
        return str.substr(commentStart + commentType.length(), endOfLine - commentStart - commentType.length());
      }
      else {
        // If no newline is found, extract and return the comment to the end of the string
        return str.substr(commentStart + commentType.length());
      }
    }

    return ""; // Return empty string if no comment is found
  }

  inline std::string removeComments(std::string str, const std::string& commentType) {
    size_t commentStart;
    while ((commentStart = str.find(commentType)) != std::string::npos) {
      size_t endOfLine = str.find('\n', commentStart);
      if (endOfLine != std::string::npos) {
        // Remove the comment, including the newline character
        str.erase(commentStart, endOfLine - commentStart + 1);
      }
      else {
        // If no newline is found, remove the comment to the end of the string
        str.erase(commentStart, std::string::npos);
        break; // No more comments after this point
      }
    }
    return str;
  }

  inline std::string removeComment(const std::string& str, const std::string& commentType) {
    size_t commentStart = str.find(commentType);
    if (commentStart != std::string::npos) {
      size_t endOfLine = str.find('\n', commentStart);

      // If a newline is found after the comment start, return the string from the start up to the comment start
      // and from the newline character to the end of the string
      if (endOfLine != std::string::npos) {
        return str.substr(0, commentStart) + str.substr(endOfLine);
      }
      else {
        // If no newline is found, return the string up to the start of the comment
        return str.substr(0, commentStart);
      }
    }

    // Return the original string if no comment is found
    return str;
  }



 inline std::string strToLower(const std::string& input) {
    std::string output = input;
    std::transform(output.begin(), output.end(), output.begin(),
      [](unsigned char c) { return std::tolower(c); });
    return output;
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

namespace github_color {
  template < class CharT, class Traits >
  constexpr
    std::basic_ostream< CharT, Traits >& reset(std::basic_ostream< CharT, Traits >& os)
  {
    return os << "**";
  }

  template < class CharT, class Traits >
  constexpr
    std::basic_ostream< CharT, Traits >& foreground_red(std::basic_ostream< CharT, Traits >& os)
  {
    return os << "**";
  }

  template < class CharT, class Traits >
  constexpr
    std::basic_ostream< CharT, Traits >& foreground_green(std::basic_ostream< CharT, Traits >& os)
  {
    return os << "";
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