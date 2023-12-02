#pragma once
#include <string>
class Yisp
{
	bool debug_mode_ = false;
	void RunFile(const std::string& path);
	void TestRunFile(const std::string& path);
	void Run(const std::string& content);
	void RunPrompt();
};

