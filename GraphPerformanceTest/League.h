#pragma once

#include <string>

class League
{
public:
	League(const std::string name) : name(name) {}

	std::string Name() { return name; }
private:
	std::string name;
};