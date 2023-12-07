
# Yisp: A Simple Lisp Interpreter in C++

## Overview
Yisp is a minimal Lisp interpreter implemented in C++. It's designed to parse and evaluate Lisp expressions, offering both script execution and an interactive Read-Eval-Print Loop (REPL) mode.

## How it Works
- **Parsing**: Utilizes a `Scanner` to tokenize Lisp code and a `Parser` to construct an abstract syntax tree (AST).
- **Evaluation**: The interpreter evaluates the AST, handling errors and producing results.
- **Interactive Mode**: Provides a REPL for dynamic expression evaluation.

## Supported Lisp Functions
Yisp supports a range of standard Lisp functions, including arithmetic, list manipulation, logical operations, and more. The following is a comprehensive list of the supported functions:
- Boolean Defenitions
  - `t` (True)
  - `()` (False)

- Arithmetic Operations:
  - `+` `add` (Add)
  - `-` `sub` (Subtract)
  - `*` `mult` (Multiply)
  - `/` `div` (Divide)

- Comparison Operations:
  - `>` `gt` (Greater Than)
  - `<` `lt` (Less Than)
  - `=` (Equal)
  - `<=` `lte` (Less Than or Equal)
  - `>=` `gte` (Greater Than or Equal)

- List Operations:
  - `cons` (Construct ConsCell)
  - `car` (First Element)
  - `cdr` (Rest of the List)

- Type Checking and Logical Operations:
  - `number?` (Is Number)
  - `list?` (Is List)
  - `nil?` (Is Nil)
  - `and?` (Logical "isNil" And)
  - `or?` (Logical "isNil" Or)
  - `symbol?` (Is Symbol)
  - `atom?` (Is Atom)

- Advanced Functionality:
  - `define` (define name (arg1 .. argN) expr)
  -  `set` (set name exp) 
## Usage
- **Script Mode**: Run Lisp scripts by passing the file path as an argument.
- **Interactive Mode**: Start the REPL by running Yisp without arguments.
- **Testing Mode**: Run a series of predefined tests with `Yisp -test`.
  - The tests folder (not the individual test folders) must be in the same directory as the exe file.
  -  Example:  Yisp folder -> Yisp.exe, /tests/ folder
## Building

- Built with MSVC (Microsoft c++/c compiler) with the C++17 Standard
- Download the repo above
- To build download and install Microsoft Visual Studio https://visualstudio.microsoft.com/ for windows or mac. Then open up the project by opening .sln file. The project and all settings should load.  At the very top of the visual studio ide click the build tab and then build solution. The Yisp.exe file should be locaed in the Yisp/x64/Debug/ folder.

- 
Yisp offers a straightforward approach to Lisp interpretation, suitable for educational purposes or simple scripting tasks.
