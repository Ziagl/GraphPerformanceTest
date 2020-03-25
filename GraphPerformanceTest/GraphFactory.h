#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include "boost/graph/adjacency_list.hpp"

#include "Country.h"
#include "League.h"
#include "Team.h"
#include "Player.h"

struct GraphDataFacility
{
    virtual ~GraphDataFacility() = default;
    virtual std::string toString() = 0;
};

using GraphData = std::shared_ptr<GraphDataFacility>;

struct GraphCountry : public Country, public GraphDataFacility
{
    GraphCountry(std::string name) : Country(name) {}
    virtual std::string toString() override { return Name(); }
};

struct GraphLeague : public League, public GraphDataFacility
{
    GraphLeague(std::string name) : League(name) {}
    virtual std::string toString() override { return Name(); }
};

struct GraphTeam : public Team, public GraphDataFacility
{
    GraphTeam(std::string name) : Team(name) {}
    virtual std::string toString() override { return Name(); }
};

struct GraphPlayer : public Player, public GraphDataFacility
{
    GraphPlayer(std::string firstname, std::string lastname) : Player(firstname, lastname) {}
    virtual std::string toString() override { return Firstname() + " " + Lastname(); }
};

enum class Node_type { COUNTRY, LEAGUE, TEAM, PLAYER, UNKNOWN };

static std::ostream& operator<<(std::ostream& os, Node_type type) {
    switch (type) {
    case Node_type::COUNTRY:   return os << "COUNTRY";
    case Node_type::LEAGUE:   return os << "LEAGUE";
    case Node_type::TEAM:    return os << "TEAM";
    case Node_type::PLAYER:   return os << "PLAYER";
    default:
    case Node_type::UNKNOWN: return os << "UNKNOWN";
    }
}

class VertexProperty 
{
public:
    VertexProperty(int id = -1, Node_type type = Node_type::UNKNOWN) : id(id), type(type) { }
    VertexProperty(int id, Node_type type, GraphData data) : id(id), type(type), data(data) { }

    std::string toString() const 
    {
        std::ostringstream oss;
        oss << *this;
        return oss.str();
    }

    int getVertexID() { return id; }
    Node_type getType() { return type; }
    GraphData getData() { return data; }

private:
    friend std::ostream& operator<<(std::ostream& os, VertexProperty const& v) {
        return os << "id " << v.id << " type " << v.type;
    }

    int id;
    Node_type type;
    GraphData data;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, VertexProperty> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
typedef boost::graph_traits<Graph>::vertex_iterator vertex_iterator;
typedef boost::graph_traits<Graph>::edge_iterator edge_iterator;
typedef boost::graph_traits<Graph>::in_edge_iterator in_edge_iterator;
typedef boost::graph_traits<Graph>::out_edge_iterator out_edge_iterator;

class GraphFactory
{
public:
	static Graph create();
    static void showVertices(const Graph &g, bool listVertices = false);
    static void showEdges(const Graph &g, bool listEdges = false);
    static void findPlayer(Graph& g, const std::tuple<std::string, std::string> name);
    static void listRandomTeam(Graph& g);
    static void moveRandomPlayerToRandomTeam(Graph& g);

private:
    static std::vector<vertex_t> getParentIds(Graph& g, vertex_t vertex);
    static std::vector<vertex_t> getChildIds(Graph& g, vertex_t vertex);
    static std::vector<vertex_t> findVerticesOfType(Graph& g, Node_type type);
};