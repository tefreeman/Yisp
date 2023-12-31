
# Yisp: A Simple Lisp Interpreter in C++

## Overview
Yisp is a minimal Lisp interpreter implemented in C++. It's designed to parse and evaluate Lisp expressions, offering both script execution and an interactive Read-Eval-Print Loop (REPL) mode.

## How it Works
- **Parsing**: Utilizes a `Scanner` to tokenize Lisp code and a `Parser` to construct an abstract syntax tree (AST).
- **Evaluation**: The interpreter evaluates the AST, handling errors and producing results.
- **Interactive Mode**: Provides a REPL for dynamic expression evaluation.

## Supported Lisp Functions
Yisp supports a range of standard Lisp functions, including arithmetic, list manipulation, logical operations, and more. All built-in functions are not case senstive. The following is a comprehensive list of the supported functions:

- Boolean Definitions
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
  - `=` (Equal, supports numbers and strings)
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

- Conditionals
  - `if` (if exprCondition expT expF)
  - `cond` (cond exprCond1, expT1, exprCond2, expT2, ...)
  
- Advanced Functionality:
  - `define` (define name (arg1 .. argN) expr)
  -  `set` (set name exp)
  -  `quote` or ` (treat next expression as a literal)
 
### Types
  - `Number` is any string parsed as a number
  - `String` string with quotes
  - `Symbol` string without quotes
  - `List` (...)


## Usage
- A pre-built Yisp.exe is provided in the main directory.
- **Script Mode**: Run Lisp scripts by passing the file path as an argument.
- **Interactive Mode**: Start the REPL by running Yisp without arguments.
- **Testing Mode**: Run a series of predefined tests with `Yisp -test`.
  - The tests folder (not the individual test folders) must be in the same directory as the exe file.
     - Example:  Yisp folder -> Yisp.exe, /tests/ folder
  -  You can add tests by dropping them in the test folder or specifying the file path an argument.

## Building
- Built with MSVC (Microsoft c++/c compiler) with the C++17 Standard
- Download the repo above
- To build download and install Microsoft Visual Studio https://visualstudio.microsoft.com/ for Windows or Mac. Then open up the project by opening .sln file. The project and all settings should load.  At the very top of the visual studio ide click the build tab and then build solution. The Yisp.exe file should be located in the Yisp/x64/Debug/ folder.

## Latest build Test results
- Any output marked as bold is counted as a test failure
- - All tests passed as of the last run.
- Automatically generated by redirecting console output
- The test files below can be found in the tests folder

### Running test: "Arithmetic.yisp"
- [ line 1] Expected: 25  Console out: 25
- [ line 2] Expected: 15  Console out: 15
- [ line 3] Expected: 24  Console out: 24
- [ line 4] Expected: 9  Console out: 9
- [ line 5] Expected: 6  Console out: 6
- [ line 6] Expected: 24  Console out: 24
- [ line 7] Expected: 5  Console out: 5
- [ line 8] Expected: 10  Console out: 10
- [ line 9] Expected: 10  Console out: 10
- [ line 10] Expected: 7  Console out: 7
- [ line 11] Expected: 6  Console out: 6
- [ line 12] Expected: 5  Console out: 5
- [ line 13] Expected: 0  Console out: 0
- [ line 14] Expected: 0  Console out: 0
- [ line 15] Expected: 5  Console out: 5
- [ line 16] Expected: 0  Console out: 0
- [ line 17] Expected: 1  Console out: 1
- [ line 18] Expected: 9  Console out: 9
- [ line 19] Expected: -3  Console out: -3
- [ line 20] Expected: 5  Console out: 5
- [ line 21] Expected: 200000  Console out: 200000
- [ line 22] Expected: 83810205  Console out: 83810205
- [ line 23] Expected: 1  Console out: 1
- [ line 24] Expected: 1000  Console out: 1000
### Running test: "blackjack.yisp"
- [ line 1] Expected: 20  Console out: 20
- [ line 2] Expected: 21  Console out: 21
- [ line 3] Expected: 15  Console out: 15
- [ line 4] Expected: 27  Console out: 27
### Running test: "comparison.yisp"
- [ line 1] Expected: T  Console out: T
- [ line 2] Expected: ()  Console out: ()
- [ line 3] Expected: T  Console out: T
- [ line 4] Expected: T  Console out: T
- [ line 5] Expected: T  Console out: T
- [ line 6] Expected: ()  Console out: ()
- [ line 7] Expected: T  Console out: T
- [ line 8] Expected: ()  Console out: ()
- [ line 9] Expected: ()  Console out: ()
- [ line 10] Expected: T  Console out: T
- [ line 11] Expected: ()  Console out: ()
- [ line 12] Expected: T  Console out: T
- [ line 13] Expected: ()  Console out: ()
- [ line 14] Expected: ()  Console out: ()
- [ line 15] Expected: T  Console out: T
- [ line 16] Expected: ()  Console out: ()
- [ line 17] Expected: T  Console out: T
- [ line 18] Expected: ()  Console out: ()
- [ line 19] Expected: ()  Console out: ()
- [ line 20] Expected: T  Console out: T
- [ line 21] Expected: ()  Console out: ()
- [ line 22] Expected: T  Console out: T
- [ line 23] Expected: ()  Console out: ()
- [ line 24] Expected: ()  Console out: ()
- [ line 25] Expected: T  Console out: T
- [ line 26] Expected: ()  Console out: ()
- [ line 27] Expected: T  Console out: T
- [ line 28] Expected: ()  Console out: ()
- [ line 29] Expected: T  Console out: T
- [ line 30] Expected: T  Console out: T
- [ line 31] Expected: ()  Console out: ()
- [ line 32] Expected: T  Console out: T
- [ line 33] Expected: ()  Console out: ()
- [ line 34] Expected: T  Console out: T
- [ line 35] Expected: T  Console out: T
- [ line 36] Expected: ()  Console out: ()
- [ line 37] Expected: T  Console out: T
- [ line 38] Expected: ()  Console out: ()
- [ line 39] Expected: T  Console out: T
- [ line 40] Expected: T  Console out: T
- [ line 41] Expected: ()  Console out: ()
- [ line 42] Expected: T  Console out: T
- [ line 43] Expected: ()  Console out: ()
- [ line 44] Expected: T  Console out: T
- [ line 45] Expected: T  Console out: T
- [ line 46] Expected: ()  Console out: ()
### Running test: "define.yisp"
- [ line 1] Expected: 10  Console out: 10
- [ line 2] Expected: 20  Console out: 20
- [ line 3] Expected: 10  Console out: 10
- [ line 4] Expected: 15  Console out: 15
- [ line 5] Expected: 2  Console out: 2
- [ line 6] Expected: 12  Console out: 12
- [ line 7] Expected: 10  Console out: 10
### Running test: "if.yisp"
- [ line 1] Expected: 100  Console out: 100
- [ line 2] Expected: 200  Console out: 200
- [ line 3] Expected: 300  Console out: 300
- [ line 4] Expected: 400  Console out: 400
- [ line 5] Expected: 500  Console out: 500
- [ line 6] Expected: 600  Console out: 600
- [ line 7] Expected: 700  Console out: 700
- [ line 8] Expected: 800  Console out: 800
- [ line 9] Expected: 900  Console out: 900
- [ line 10] Expected: 1000  Console out: 1000
- [ line 11] Expected: 1100  Console out: 1100
- [ line 12] Expected: 1200  Console out: 1200
- [ line 13] Expected: 1300  Console out: 1300
- [ line 14] Expected: 1400  Console out: 1400
- [ line 15] Expected: 1500  Console out: 1500
- [ line 16] Expected: 1600  Console out: 1600
- [ line 17] Expected: 1800  Console out: 1800
- [ line 18] Expected: 1900  Console out: 1900
- [ line 19] Expected: 2100  Console out: 2100
- [ line 20] Expected: 2200  Console out: 2200
### Running test: "isfuncs.yisp"
- [ line 1] Expected: T  Console out: T
- [ line 2] Expected: ()  Console out: ()
- [ line 3] Expected: ()  Console out: ()
- [ line 4] Expected: ()  Console out: ()
- [ line 5] Expected: T  Console out: T
- [ line 6] Expected: ()  Console out: ()
- [ line 7] Expected: ()  Console out: ()
- [ line 8] Expected: ()  Console out: ()
- [ line 9] Expected: T  Console out: T
- [ line 10] Expected: T  Console out: T
- [ line 11] Expected: ()  Console out: ()
- [ line 12] Expected: ()  Console out: ()
- [ line 13] Expected: T  Console out: T
- [ line 14] Expected: T  Console out: T
- [ line 15] Expected: T  Console out: T
- [ line 16] Expected: ()  Console out: ()
- [ line 17] Expected: ()  Console out: ()
- [ line 18] Expected: T  Console out: T
- [ line 19] Expected: T  Console out: T
- [ line 20] Expected: ()  Console out: ()
- [ line 21] Expected: ()  Console out: ()
- [ line 22] Expected: ()  Console out: ()
- [ line 23] Expected: T  Console out: T
- [ line 24] Expected: ()  Console out: ()
- [ line 25] Expected: ()  Console out: ()
- [ line 26] Expected: ()  Console out: ()
- [ line 27] Expected: T  Console out: T
- [ line 28] Expected: T  Console out: T
- [ line 29] Expected: T  Console out: T
- [ line 30] Expected: ()  Console out: ()
### Running test: "lisp_exam_1.yisp"
- [ line 1] Expected: 0  Console out: 0
- [ line 2] Expected: 1  Console out: 1
- [ line 3] Expected: 1  Console out: 1
- [ line 4] Expected: 2  Console out: 2
- [ line 5] Expected: 3  Console out: 3
### Running test: "list.yisp"
- [ line 1] Expected: (1 . 2)  Console out: (1 . 2)
- [ line 2] Expected: ("a" . "b")  Console out: ("a" . "b")
- [ line 3] Expected: ((1 . 2) . 3)  Console out: ((1 . 2) . 3)
- [ line 4] Expected: (1 . (2 . 3))  Console out: (1 . (2 . 3))
- [ line 5] Expected: (() . 2)  Console out: (() . 2)
- [ line 6] Expected: (1)  Console out: (1)
- [ line 7] Expected: 1  Console out: 1
- [ line 8] Expected: "a"  Console out: "a"
- [ line 9] Expected: (1 . 2)  Console out: (1 . 2)
- [ line 10] Expected: 1  Console out: 1
- [ line 11] Expected: ()  Console out: ()
- [ line 12] Expected: 1  Console out: 1
- [ line 13] Expected: 2  Console out: 2
- [ line 14] Expected: "b"  Console out: "b"
- [ line 15] Expected: 3  Console out: 3
- [ line 16] Expected: (2 . 3)  Console out: (2 . 3)
- [ line 17] Expected: 2  Console out: 2
- [ line 18] Expected: ()  Console out: ()
- [ line 19] Expected: 1  Console out: 1
- [ line 20] Expected: 2  Console out: 2
- [ line 21] Expected: 2  Console out: 2
- [ line 22] Expected: 3  Console out: 3
- [ line 23] Expected: (())  Console out: (())
- [ line 24] Expected: ()  Console out: ()
- [ line 25] Expected: ()  Console out: ()
- [ line 26] Expected: ((1 . (2 . 3)) . (4 . 5))  Console out: ((1 . (2 . 3)) . (4 . 5))
- [ line 27] Expected: (1 . (2 . 3))  Console out: (1 . (2 . 3))
- [ line 28] Expected: (4 . 5)  Console out: (4 . 5)
