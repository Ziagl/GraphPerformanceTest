#pragma once

#include <string>

class Player
{
public:
	Player(const std::string firstname, const std::string lastname) : firstname(firstname), lastname(lastname) {}

	std::string Firstname() { return firstname; }
	std::string Lastname() { return lastname; }

private:
	std::string firstname;
	std::string lastname;
};