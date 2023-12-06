#include "Yisp.h"
#include <iostream>
#include "Types.h"
#include "Parser.cpp"
#include "Scanner.h"
#include <fstream>
#include "util.cpp"

using namespace types;

	void Yisp::RunFile(const std::string& path)
	{
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
      throw std::runtime_error("Unable to open file.");
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);

    if (file.read(buffer.data(), size)) {
      std::string content(buffer.begin(), buffer.end());
      std::vector<std::string> out = Run(content);

      for(const auto& result : out) {
        std::cout << result << std::endl;
      }
    }
    else {
      throw std::runtime_error("Unable to read file.");
    }
	}

	void Yisp::TestRunFile(const std::string& path)
	{
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
      throw std::runtime_error("Unable to open file.");
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);

    if (file.read(buffer.data(), size)) {
      std::string content(buffer.begin(), buffer.end());
      RunTest(content);
  
    }
    else {
      throw std::runtime_error("Unable to read file.");
    }
	}

  bool Yisp::RunTest(const std::string& content)
  {
    bool successfulTest = true;

    std::vector<std::string> expectedOutputs;
    std::istringstream iss(content);
    std::string line;

    while (std::getline(iss, line)) {

      std::string expected = yisp_util::extractComment(line, ";expect:");
      yisp_util::trim(expected);

      if (!expected.empty())
         expectedOutputs.push_back(expected);
    }
     
    std::vector<std::string> result = Run(content);

    if (result.size() != expectedOutputs.size()) {
          std::cout << ansi::foreground_red;
          std::cout << "Expected " << expectedOutputs.size() << " results, got " << result.size() << std::endl;
          std::cout << ansi::reset;
          return false;
    }

    for(int i=0; i < expectedOutputs.size(); i++) {
      if (evalTestAndDisplay(expectedOutputs[i], result[i]) == false)
        successfulTest = false;
      
    }

    return successfulTest;
  }

  bool Yisp::evalTestAndDisplay(std::string& expected, std::string& result)
  {
    bool testIsSuccess;

    if (yisp_util::isRealNumber(expected) && yisp_util::isRealNumber(result))
      testIsSuccess = std::stod(expected) == std::stod(result);
    else if(expected.find("Error") != std::string::npos && result.find("Error") != std::string::npos)
      testIsSuccess = true;
    else
      testIsSuccess = expected == result;

    if (testIsSuccess) {
      std::cout << ansi::foreground_green;
      std::cout << "Expected: " << expected;
      std::cout << "  Got: " << result;
      std::cout << ansi::reset;

    }
    else {
      std::cout << ansi::foreground_red;
      std::cout << "Expected: " << expected;
      std::cout << "  Got: " << result;
      std::cout << ansi::reset;
    }
    std::cout << std::endl;
    return testIsSuccess;
  }

	std::vector<std::string> Yisp::Run(const std::string& content)
	{

    Scanner scanner;
    Environment env;
    std::vector<std::string> out;

   // try {
     List tokens = scanner.parse(content);

     for (auto token : tokens)
     {
     try {
       std::any val = eval(token, env);
       std::string printStr = stringifyOutput(val);
       if (!printStr.empty())
          out.push_back(printStr);

     } catch (YispRuntimeError& e) {
      out.push_back(e.get());
      }
   }

     return out;

	}


  std::string Yisp::stringifyOutput(const std::any& exp) {
    if (isList(exp)) {
      const List& lst = toList(exp);

      // Check if the list is a cons cell
      if (isConsCell(exp)) {
        // Assuming a cons cell has exactly two elements
        if(lst.size() == 2) 
          return "(" + stringifyOutput(lst[0]) + " . " + stringifyOutput(lst[1]) + ")";
        else
          return   stringifyOutput(lst[0]);
      }
      else {
        // Handle as a regular list
        std::string result = "(";
        for (size_t i = 0; i < lst.size(); ++i) {
          if (i > 0) {
            result += " ";
          }
          result += stringifyOutput(lst[i]);
        }
        result += ")";
        return result;
      }
    }
    else {
      // Handle non-list types
      return atomToStr(exp);
    }
  }


  void Yisp::repl() {
    std::string prompt = "yisp> ";
    Scanner scanner;
    Environment env;
    std::string input;
    while (true) {
      std::cout << prompt;
      std::getline(std::cin, input);
      if (input.empty()) continue; // Handle empty input

    //  try {
        List tokens = scanner.parse(input);
        std::any val = eval(tokens[0], env);
       
       if (val.has_value()) {
          std::cout << stringifyOutput(val) << std::endl;
        }
//    }
 //     catch (YispRuntimeError& e) {
  //      e.display();
  //   }
    }
  }
