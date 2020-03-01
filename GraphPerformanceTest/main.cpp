/*
 * The purpose of this program is to benchmark different types of data organisation
 * the question: is there a performance boost with a graph structure instead a normal
 * class hierarchy structure and are there benefits in the data access?
 *
 * the example for this is the following: create a data structure for the world soccer
 * association. Each team consists of at least 11 players, a league of at least 10 teams,
 * a country of at least 2 leagues and every country should have soccer leages.
 * Data access examples: 
 *   * search for a player name
 *   * list all players of a team
 *   * move a player for one team to another
 */

#include <iostream>

int main()
{
    std::cout << "Graph Benchmark" << std::endl;

    return 0;
}