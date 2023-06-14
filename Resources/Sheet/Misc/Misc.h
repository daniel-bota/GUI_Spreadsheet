#pragma once
#include <string>
#include <vector>
#include <format>

class Misc
{
public:
	static std::vector<std::string> Split(const std::string& input, char delimiter);
	static std::string Trim(const std::string& input);
    static bool IsNumber(const std::string& input, double& output);
	static std::string GenerateRowTitle(int index);
	static std::string GenerateColTitle(int index);
};

