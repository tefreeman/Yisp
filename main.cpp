#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <filesystem>

#include <vector>
#include <any>

#include "Yisp.h"
int main(int argc, char* argv[]) {


  if (argc > 2) {
    std::cout << "Usage: lox [script]" << std::endl;
    std::exit(64);
  }
  else if (argc == 2) {
    if (strcmp(argv[1], "-test") == 0) {
      // do test
      std::filesystem::path cwd = std::filesystem::current_path();
      std::string path = cwd.string() + "/tests";

      std::filesystem::recursive_directory_iterator it(path);

      for (auto& p : it) {
        if (p.path().extension() == ".lox") {
        }
      }
    }
    else if (strcmp(argv[1], "-debug") == 0) {
    }
    else {
    }
  }
  else {
    Yisp yisp;
    yisp.repl();
  }

  return 0;
} 
