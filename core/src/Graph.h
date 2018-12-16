#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <random>

class Node
{
	private:
	std::string m_name;
	std::vector<char> bearing;
	std::vector<Node*> m_nodes;
	
	public:
	Node(std::string &name)
	{
		this->m_name = name;
		this->m_nodes.reserve(1);
		std::cout<<"Name of Node = "<<m_name<<std::endl;
	}
	~Node()
	{
		for (unsigned int i=0; i<this->m_nodes.size();i++)
		{
			printf("Node Destructor Called");
			delete &this->m_nodes[i];			
		}
	}
};

class Graph
{
	std::vector<Node*> m_map;
	
	public:
	Graph()
	{
		GraphGeneration();
	}
	
	~Graph()
	{
		printf("Graph Destructor Called\n");
		for(unsigned i =0; i<m_map.size();i++)
		{			
			delete &(*m_map[i]);	
			std::cout<<m_map[i]<<std::endl;
		}	
	}
	private:
	void GraphGeneration()
	{
		//array for name/n/e/s/w
		//Parsing();
		printf("GraphGeneration\n");
		std::string x  = "A";
		std::string y = "B";
		Node* n = new Node(x);
		Node* m = new Node(y);
		
		this->m_map.push_back(n);
		this->m_map.push_back(m);	
	}		
};
#endif