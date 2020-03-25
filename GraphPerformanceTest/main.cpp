/*
 * The purpose of this program is to benchmark different types of data organisation
 * the question: is there a performance boost with a graph structure instead a normal
 * class hierarchy structure and are there benefits in the data access?
 *
 * The example for this is the following: create a data structure for the world soccer
 * association. Each team consists of at least 11 players, a league of at least 10 teams,
 * a country of at least 2 leagues and every country should have soccer leages.
 * Data access examples: 
 *   * search for a player name
 *   * list all players of a team
 *   * move a player from one team to another
 */

#include <iostream>
#include <algorithm>
#include "ClassHierarchyFactory.h"
#include "NameGenerator.h"
#include "RandomNumberGenerator.h"
#include "GraphFactory.h"

int main()
{
    std::cout << "Graph Benchmark" << std::endl;

    NameGenerator nameGenerator;

    // create class structure data
    {
        std::cout << "create class data structure" << std::endl;
        std::cout << "***************************" << std::endl << std::endl;
        auto data = ClassHierarchyFactory::create();

        // search for a random name
        auto randomName = nameGenerator.createName();
        std::cout << "Search started for: " << std::get<1>(randomName) << std::endl;
        std::for_each(data.begin(), data.end(), [randomName](auto country) {
            //std::cout << country.Name() << std::endl;
            std::for_each(country.leagues.begin(), country.leagues.end(), [randomName, country](auto league) mutable {
                //std::cout << league.Name() << std::endl;
                std::for_each(league.teams.begin(), league.teams.end(), [randomName, country, league](auto team) mutable {
                    //std::cout << team.Name() << std::endl;
                    std::for_each(team.player.begin(), team.player.end(), [randomName, country, league, team](auto player) mutable {
                        if (std::get<1>(randomName) == player.Lastname())
                        {
                            std::cout << "    " << player.Firstname() << " " << player.Lastname() << " (" << team.Name() << ", " << league.Name() << ", " << country.Name() << ")" << std::endl;
                        }
                        });
                    });
                });
            });

        // list players of a random team
        int randomCountry = RandomNumberGenerator::randomNumber(0, static_cast<int>(data.size()));
        auto country = data[randomCountry];
        int randomLeague = RandomNumberGenerator::randomNumber(0, static_cast<int>(country.leagues.size()));
        auto league = country.leagues[randomLeague];
        int randomTeam = RandomNumberGenerator::randomNumber(0, static_cast<int>(league.teams.size()));
        auto team = league.teams[randomTeam];
        std::cout << "List " << team.Name() << " (" << league.Name() << ", " << country.Name() << ")" << std::endl;
        std::for_each(team.player.begin(), team.player.end(), [](auto player) { std::cout << "    " << player.Firstname() << " " << player.Lastname() << std::endl; });

        // move random player to random team
        int randomPlayer = RandomNumberGenerator::randomNumber(0, static_cast<int>(team.player.size()));
        auto player = team.player[randomPlayer];
        std::cout << "Move Player " << player.Firstname() << " " << player.Lastname() << " from " << team.Name() << " (" << league.Name() << ", " << country.Name() << ") to ";
        int randomCountryNew = RandomNumberGenerator::randomNumber(0, static_cast<int>(data.size()));
        auto countryNew = data[randomCountryNew];
        int randomLeagueNew = RandomNumberGenerator::randomNumber(0, static_cast<int>(country.leagues.size()));
        auto leagueNew = country.leagues[randomLeagueNew];
        int randomTeamNew = RandomNumberGenerator::randomNumber(0, static_cast<int>(league.teams.size()));
        auto teamNew = league.teams[randomTeamNew];
        std::cout << teamNew.Name() << " (" << leagueNew.Name() << ", " << countryNew.Name() << ")" << std::endl;

        teamNew.player.insert(teamNew.player.end(),
            std::make_move_iterator(team.player.begin() + randomPlayer),
            std::make_move_iterator(team.player.begin() + randomPlayer + 1)
            );
        team.player.erase(team.player.begin() + randomPlayer, team.player.begin() + randomPlayer + 1);

        std::cout << "List old " << team.Name() << " (" << league.Name() << ", " << country.Name() << ")" << std::endl;
        std::for_each(team.player.begin(), team.player.end(), [](auto player) { std::cout << "    " << player.Firstname() << " " << player.Lastname() << std::endl; });
        std::cout << "List new " << teamNew.Name() << " (" << leagueNew.Name() << ", " << countryNew.Name() << ")" << std::endl;
        std::for_each(teamNew.player.begin(), teamNew.player.end(), [](auto player) { std::cout << "    " << player.Firstname() << " " << player.Lastname() << std::endl; });
    }

    // create graph structure data
    {
        std::cout << std::endl << std::endl;
        std::cout << "create graph data structure" << std::endl;
        std::cout << "***************************" << std::endl << std::endl;
        auto graph = GraphFactory::create();
        //GraphFactory::showVertices(graph);
        //GraphFactory::showEdges(graph);

        // search for a random name
        auto randomName = nameGenerator.createName();
        std::cout << "Search started for: " << std::get<1>(randomName) << std::endl;
        GraphFactory::findPlayer(graph, randomName);

        // list players of a random team
        GraphFactory::listRandomTeam(graph);

        // move random player to random team
        GraphFactory::moveRandomPlayerToRandomTeam(graph);
    }

    return 0;
}