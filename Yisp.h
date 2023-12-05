#pragma once
#include <string>
#include <any>
#include <vector>
#include <iostream>

class Yisp
{
private: 
	bool RunTest(const std::string& content);
	bool evalTestAndDisplay(std::string& output, std::string& expected);
public:
	void RunFile(const std::string& path);
	void TestRunFile(const std::string& path);
	std::vector<std::string> Run(const std::string& content);
	std::string stringifyOutput(const std::any& exp);




	void repl();
};

