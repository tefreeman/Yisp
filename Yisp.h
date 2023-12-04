#pragma once
#include <string>
#include <any>

class Yisp
{
public:
	bool debug_mode_ = false;
	void RunFile(const std::string& path);
	void TestRunFile(const std::string& path);
	void Run(const std::string& content);

	std::string schemestr(const std::any& exp);
	void repl();
};

