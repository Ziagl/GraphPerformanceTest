#pragma once

#include <vector>
#include <tuple>
#include <string>

class NameGenerator
{
public:
	NameGenerator();

	std::tuple<std::string, std::string> createName();

private:
	void loadFromFile();

	std::vector<std::string> firstname;
	std::vector<std::string> lastname;
};