#pragma once

#include "Country.h"
#include "League.h"
#include "Team.h"
#include "Player.h"
#include <vector>

struct HierarchyTeam : public Team
{
	HierarchyTeam(const std::string name) : Team(name) {}
	std::vector<Player> player;
};

struct HierarchyLeague : public League
{
	HierarchyLeague(const std::string name) : League(name) {}
	std::vector<HierarchyTeam> teams;
};

struct HierarchyCountry : public Country
{
	HierarchyCountry(const std::string name) : Country(name) {}
	std::vector<HierarchyLeague> leagues;
};



class ClassHierarchyFactory
{
public:
	static std::vector<HierarchyCountry> create();
};