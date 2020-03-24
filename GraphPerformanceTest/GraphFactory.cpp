#include "GraphFactory.h"
#include "RandomNumberGenerator.h"
#include "NameGenerator.h"

Graph GraphFactory::create()
{
	NameGenerator ng;

	int numberCountries = 250;
	int numberLeagues = 2;
	int numberTeams = 18;
	int numberPlayers = 20;

	Graph g;
	int id = 0;

	//boost::property_map <Graph, boost::vertex_name_t>::type name_map = boost::get(boost::vertex_name, g);
	//boost::adjacency_list<>::vertex_descriptor root = boost::add_vertex(g);
	auto root = boost::add_vertex(VertexProperty{ id++, Node_type::UNKNOWN, GraphData() }, g);

	for (int i = 0; i < numberCountries; ++i)
	{
		vertex_t c = boost::add_vertex(VertexProperty{ id++, Node_type::COUNTRY, GraphCountry("Country " + std::to_string(i + 1)) }, g);
		//g[c].country = Country("Country " + std::to_string(i + 1));
		//boost::put(name_map, c, "Country " + std::to_string(i + 1));

		for (int j = 0; j < numberLeagues; ++j)
		{
			vertex_t l = boost::add_vertex(VertexProperty{ id++, Node_type::LEAGUE, GraphLeague("League " + std::to_string(j + 1)) },g);
			//g[l].league = League("League " + std::to_string(j + 1));
			//boost::put(name_map, l, "League " + std::to_string(j + 1));

			for (int x = 0; x < numberTeams; ++x)
			{
				vertex_t t = boost::add_vertex(VertexProperty{ id++, Node_type::TEAM, GraphTeam("Team " + std::to_string(x + 1)) },g);
				//g[t].team = Team("Team " + std::to_string(x + 1));
				//boost::put(name_map, t, "Team " + std::to_string(x + 1));

				for (int y = 0; y < numberPlayers; ++y)
				{
					auto nameTuple = ng.createName();
					vertex_t p = boost::add_vertex(VertexProperty{ id++, Node_type::PLAYER, GraphPlayer(std::get<0>(nameTuple), std::get<1>(nameTuple)) }, g);
					//g[p].player = Player(std::get<0>(nameTuple), std::get<1>(nameTuple));
					//boost::put(name_map, p, std::get<0>(nameTuple) + " " + std::get<1>(nameTuple));
				}
			}
		}
	}

	return g;
}

void GraphFactory::showVertices(Graph g)
{
	std::pair<vertex_iterator, vertex_iterator> vi = boost::vertices(g);
	std::cout << " Number of vertices are " << std::endl;
	for (vertex_iterator i = vi.first; i != vi.second; ++i)
	{
		std::cout << g[*i].toString() << std::endl;
	}
}