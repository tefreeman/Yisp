#include <filesystem>
#include <iostream>
#include <string>
#include "Yisp.h"
#include <fstream>

#define TEST_FOLDER "\\tests"
#define FILE_EXTENSION ".yisp"
#define REDIRECT_TO_OUT_FILE false


int main(int argc, char* argv[]) {


// Redirect cout to out.txt
  if (REDIRECT_TO_OUT_FILE)
  {
  std::locale::global(std::locale("en_US.UTF-8"));
  std::ofstream out("out.txt");
  auto* coutbuf = std::cout.rdbuf();
  std::cout.rdbuf(out.rdbuf());
  }

  if (argc > 2) {
    std::cout << "Usage: Yisp, Yisp [script], Yisp -test" << std::endl;
    std::exit(64);
  }
  else if (argc == 2) {
    if (strcmp(argv[1], "-test") == 0) {

      // Run all tests in tests folder recursively
      std::filesystem::path cwd = std::filesystem::current_path();
      std::string path = cwd.string() + TEST_FOLDER;
      std::filesystem::recursive_directory_iterator it(path);

      for (auto& p : it) {
        if (p.path().extension() == FILE_EXTENSION) {
          std::cout << "### Running test: " << p.path().filename() << std::endl;
          Yisp yisp;
          yisp.TestFile(p.path().string());
        }
      }
    }
    else {
      // Run a single test file by name (in test folder) or path
      std::filesystem::path cwd = std::filesystem::current_path();
      std::string path = cwd.string() + TEST_FOLDER;
      std::filesystem::recursive_directory_iterator it(path);
      Yisp yisp;

      // If it's a file name in tests folder
      for (auto& p : it) {
        if (p.path().extension() == FILE_EXTENSION && p.path().filename().string() == argv[1]) {
          std::cout << "Running file: " << p.path() << std::endl;
          yisp.RunFile(p.path().string());
          return 0;
        }
      }
      // Must be a file path
      std::cout << "Running file at: " << argv[1];
      yisp.TestFile(argv[1]);
    }
  }
  else {

    // Run REPL if no arguments
    Yisp yisp;
    yisp.repl();
  }

  return 0;
}
