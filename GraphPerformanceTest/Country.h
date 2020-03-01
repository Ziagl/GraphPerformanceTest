#pragma once

#include <string>

class Country
{
public:
	Country(const std::string name) : name(name) {}

	std::string Name() { return name; }
private:
	std::string name;
};