#include "Yisp.h"
#include <iostream>
#include "Types.h"
#include "Parser.cpp"
#include "Scanner.h"
using namespace types;

	void Yisp::RunFile(const std::string& path)
	{
	}

	void Yisp::TestRunFile(const std::string& path)
	{
	}

	void Yisp::Run(const std::string& content)
	{
	}


  std::string Yisp::schemestr(const std::any& exp) {
    if (exp.type() == typeid(List)) {
      const List& lst = std::any_cast<List>(exp);
      std::string result = "(";
      for (const auto& item : lst) {
        if (&item != &lst[0]) {
          result += " ";
        }
        result += schemestr(item);
      }
      result += ")";
      return result;
    }
    else {
      if (exp.type() == typeid(bool)) {
        bool val = std::any_cast<bool>(exp);
        return val ? "T" : "()";
      }
      if (exp.type() == typeid(std::string)) {
        return std::any_cast<std::string>(exp);
      }
      if (exp.type() == typeid(Number)) {
        return std::to_string(std::any_cast<Number>(exp));
      }

    }
  }

  void Yisp::repl() {
    std::string prompt = "lis.py> ";
    Scanner scanner;
    Environment env;
    std::string input;
    while (true) {
      std::cout << prompt;
      std::getline(std::cin, input);
      if (input.empty()) continue; // Handle empty input

   //   try {
        List tokens = scanner.parse(input);
        std::any val = eval(tokens, env);
       
       if (val.has_value()) {
          std::cout << schemestr(val) << std::endl;
        }
   //   }
    //  catch (const std::exception& e) {
     //   std::cerr << "Error: " << e.what() << std::endl;
    //  }
    }
  }
