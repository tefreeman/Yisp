#include "Yisp.h"
#include <iostream>
#include "Types.h"
#include "Parser.cpp"
#include "Scanner.h"
#include <fstream>
#include <sstream>
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

	void Yisp::TestFile(const std::string& path)
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

      
      // grab the expected test output
      std::string expected = yisp_util::extractComment(line, ";expect:");
      yisp_util::trim(expected); // get rid of extra whitespace

      if (!expected.empty())
         expectedOutputs.push_back(expected);
    }
    
    // Interpret the file and get all outputs
    std::vector<std::string> outputs = Run(content);

    if (outputs.size() != expectedOutputs.size()) {
          std::cout << ansi::foreground_red;
          std::cout << "Expected " << expectedOutputs.size() << " results, got " << outputs.size() << std::endl;
          std::cout << ansi::reset;
          return false;
    }
    int lineNumber = 0;
    for(int i=0; i < expectedOutputs.size(); i++) {
      lineNumber++;
      if (evalTestAndDisplay(expectedOutputs[i], outputs[i], lineNumber) == false)
        successfulTest = false;
      
    }

    return successfulTest;
  }

  bool Yisp::evalTestAndDisplay(std::string& expected, std::string& result, int lineNum)
  {
    bool testIsSuccess;

    if (yisp_util::isRealNumber(expected) && yisp_util::isRealNumber(result))
      testIsSuccess = std::stod(expected) == std::stod(result);
    else if(expected.find("Error") != std::string::npos && result.find("Error") != std::string::npos)
      testIsSuccess = true;
    else
      testIsSuccess = (expected == result);
    
    std::cout << "- ";
    if (testIsSuccess) {
      std::cout << ansi::foreground_green;
      std::cout << "[ line " << lineNum << "] ";
      std::cout << "Expected: " << expected;
      std::cout << "  Console out: " << result;
      std::cout << ansi::reset;

    }
    else {

      std::cout << ansi::foreground_red;
      std::cout << "[ line " << lineNum << "] ";
      std::cout << "Expected: " << expected;
      std::cout << "  Console out: " << result;
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

    
    try {
        List tokens = scanner.parse(input);
        std::any val = eval(tokens[0], env);
       
       if (val.has_value()) {
          std::cout << stringifyOutput(val) << std::endl;
        }
    }
      catch (YispRuntimeError& e) {
        e.display();
     }
    }
  }
