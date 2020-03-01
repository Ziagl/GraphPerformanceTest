#include "ClassHierarchyFactory.h"
#include "RandomNumberGenerator.h"
#include "NameGenerator.h"

std::vector<HierarchyCountry> ClassHierarchyFactory::create()
{
	NameGenerator ng;
	std::vector<HierarchyCountry> countries;

	int numberCountries = 250;
	int numberLeagues = 2;
	int numberTeams = 18;
	int numberPlayers = 20;
	for (int i = 0; i < numberCountries; ++i)
	{
		HierarchyCountry c("Country " + std::to_string(i + 1));
		
		for (int j = 0; j < numberLeagues; ++j)
		{
			HierarchyLeague l("League " + std::to_string(j + 1));

			for (int x = 0; x < numberTeams; ++x)
			{
				HierarchyTeam t("Team " + std::to_string(x + 1));

				for (int y = 0; y < numberPlayers; ++y)
				{
					auto nameTuple = ng.createName();
					Player p(std::get<0>(nameTuple), std::get<1>(nameTuple));

					t.player.push_back(p);
				}

				l.teams.push_back(t);
			}

			c.leagues.push_back(l);
		}

		countries.push_back(c);
	}

	return countries;
}