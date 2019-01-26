#pragma once

#include "CustomSystem.h"

#include <vector>
#include <iostream>
#include <limits.h>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>

enum class Bearing
{
	NORTH = 0, EAST, SOUTH, WEST
};
class Node
{
private:
	std::string m_name;
	bool m_treasure=FALSE;
	std::vector<Bearing> m_bearing;//0=north,1=east,2=south,3=west
	std::vector<Node*> m_nodes;	//list of pointers to nodes

	void AssingNodes(Bearing p, const std::string x, std::vector<Node*> &m_map);

public:

	Node(std::string name);

	~Node();

	Node(const Node&) = delete;

	const std::vector<Bearing>& GetAvailableBearings();

	Node* GetExit(Bearing x);

	std::string GetName();

	void SetBearings(std::string North_node, std::string East_node, std::string South_node, const std::string West_node, std::vector<Node*> &m_map);

	void setTreasure();

	bool getTreasureBool();
};

class Graph
{
public:
	Graph();

	~Graph();

	Graph(const Graph&) = delete;

	int GetTotalNodes();

	Node* GetNode(int x);

	Node* GetNode(std::string x);

	int getGenType();

	std::string getFileName();

	Node* getEndGameNode();

	void setGraphTreasure();

	bool getTreasureBool();

private:
	bool g_treasure = FALSE;
	std::vector<Node*> m_map;
	Node* endgameNode;

    int genType;
    std::string fileName;

	int GraphGeneration();

	std::vector<std::string>* Parsing();

	std::vector<std::string>* staticGeneration();

	std::vector<std::string>* randomGeneration();
};

class Player
{
private:
	int steps = 0;
	Node* CurrentNode;
	std::vector<Node*> treasureList;

	bool treasureObtained();

public:
	Player(Node* x);

	Node* GetCurrentNode();

	void SetCurrentNode(Node* x);

	void SetSteps();

	int GetSteps();

	int getTreasureCount();

	void NavigateOptions();

};
