#pragma once
#include <string>
#include <any>

class Yisp
{
public:
	bool debug_mode_ = false;
	void RunFile(const std::string& path);
	void TestRunFile(const std::string& path);
	std::string Run(const std::string& content);

	std::string stringifyOutput(const std::any& exp);
	void repl();
};

