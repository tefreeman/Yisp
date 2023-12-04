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
    std::cout << "Usage: Yisp, Yisp [script], Yisp -test" << std::endl;
    std::exit(64);
  }
  else if (argc == 2) {
    if (strcmp(argv[1], "-test") == 0) {
      // do test
      std::filesystem::path cwd = std::filesystem::current_path();
      std::string path = cwd.string() + "/tests";
      std::filesystem::recursive_directory_iterator it(path);

      for (auto& p : it) {
        if (p.path().extension() == ".yisp") {
          std::cout << "Running test: " << p.path().filename() << std::endl;
          Yisp yisp;
          yisp.TestRunFile(p.path().string());
        }
      }
    }
    else {
      std::filesystem::path cwd = std::filesystem::current_path();
      std::string path = cwd.string() + "/tests";
      std::filesystem::recursive_directory_iterator it(path);
      Yisp yisp;
      // If it's a file name in tests folder
      for (auto& p : it) {
        if (p.path().extension() == ".yisp" && p.path().filename().string() == argv[1]) {
          std::cout << "Running file: " << p.path() << std::endl;
          yisp.RunFile(p.path().string());
          return 0;
        }
      }
      // Must be a file path
      std::cout << "Running file at: " << argv[1];
      yisp.TestRunFile(argv[1]);
    }
  }
  else {
    Yisp yisp;
    yisp.repl();
  }

  return 0;
} 
