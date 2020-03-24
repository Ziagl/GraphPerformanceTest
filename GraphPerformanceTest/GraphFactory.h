#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include "boost/graph/adjacency_list.hpp"

#include "Country.h"
#include "League.h"
#include "Team.h"
#include "Player.h"

struct GraphData
{
    virtual std::string toString() { return "root"; };
};

struct GraphCountry : public Country, public GraphData
{
    GraphCountry(std::string name) : Country(name) {}
    virtual std::string toString() { return Name(); }
};

struct GraphLeague : public League, public GraphData
{
    GraphLeague(std::string name) : League(name) {}
    virtual std::string toString() { return Name(); }
};

struct GraphTeam : public Team, public GraphData
{
    GraphTeam(std::string name) : Team(name) {}
    virtual std::string toString() { return Name(); }
};

struct GraphPlayer : public Player, public GraphData
{
    GraphPlayer(std::string firstname, std::string lastname) : Player(firstname, lastname) {}
    virtual std::string toString() { return Firstname() + " " + Lastname(); }
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

    std::string toString() const {
        std::ostringstream oss;
        oss << *this;
        return oss.str();
    }

    int getVertexID() { return id; }

private:
    friend std::ostream& operator<<(std::ostream& os, VertexProperty const& v) {
        return os << "id " << v.id << " type " << v.type;
    }

    int id;
    Node_type type;
    GraphData data;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperty> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
typedef boost::graph_traits<Graph>::vertex_iterator vertex_iterator;

class GraphFactory
{
public:
	static Graph create();
    static void showVertices(Graph g);
};