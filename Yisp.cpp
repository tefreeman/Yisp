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
      std::cout << Run(content) << std::endl;
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

      std::string expected = yisp_util::extractComment(content, ";expect:");
      yisp_util::trim(expected);
      std::string result = Run(content);

      if (expected != result) {
        std::cout << "Expected: " << expected << std::endl;
        std::cout << "Got: " << result << std::endl;
        std::cout << "Test failed." << std::endl;
      }
      else {
        std::cout << "Test passed." << std::endl;
      }
    }
    else {
      throw std::runtime_error("Unable to read file.");
    }
	}

	std::string Yisp::Run(const std::string& content)
	{

    Scanner scanner;
    Environment env;

    try {
     List tokens = scanner.parse(content);
     std::any val = eval(tokens, env);
     return stringifyOutput(val);
    }
    catch (YispRuntimeError& e) {
      e.display();
    }
	}


  std::string Yisp::stringifyOutput(const std::any& exp) {
    if (isList(exp)) {
      const List& lst = toList(exp);
      std::string result = "(";
      for (const auto& item : lst) {
        if (&item != &lst[0]) {
          result += " ";
        }
        result += stringifyOutput(item);
      }
      result += ")";
      return result;
    }
    else {
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
        std::any val = eval(tokens, env);
       
       if (val.has_value()) {
          std::cout << stringifyOutput(val) << std::endl;
        }
    }
      catch (YispRuntimeError& e) {
        e.display();
     }
    }
  }
