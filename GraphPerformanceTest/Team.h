#pragma once

#include <string>

class Team
{
public:
	Team(const std::string name) :name(name) {}

	std::string Name() { return name; }
private:
	std::string name;
};