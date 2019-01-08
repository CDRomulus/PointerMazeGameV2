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
	
	std::vector<Bearing> m_bearing;//0=north,1=east,2=south,3=west
	std::vector<Node*> m_nodes;	//list of pointers to nodes
	
	void AssingNodes(Bearing p, const std::string x, std::vector<Node*> &m_map)
	{
		for(unsigned int i =0; i<m_map.size();i++)
		{
			if((*m_map[i]).GetName()==x)
			{
				m_bearing.push_back(p);
				m_nodes.push_back(m_map[i]);
				break;
			}
		}
	}

	public:
	
	Node(std::string name)
	{		
		this->m_name = name;	
	}
	~Node()
	{	
		std::cout << "Node Destructor Called: " << m_name << "\n";
		for(unsigned int x;x<m_nodes.size();x++)
		{
			m_nodes[x]=nullptr;
		}
		
	}

	Node(const Node&) = delete;

	const std::vector<Bearing>& GetAvailableBearings()
	{
		return m_bearing;
	}
	Node* GetExit(Bearing x)
	{
		for(unsigned int i =0; i<m_bearing.size();i++)
		{
			if(m_bearing[i] ==x)
			{
				return m_nodes[i];
			}
		}
		return nullptr;
	}
	
	std::string GetName()
	{
		return m_name;
	}
	void SetBearings(std::string North_node, std::string East_node, std::string South_node, const std::string West_node, std::vector<Node*> &m_map)
	{
		
		if(North_node!="*")
		{
			AssingNodes(Bearing::NORTH,North_node,m_map);
		}
		if(East_node!="*")
		{
			AssingNodes(Bearing::EAST,East_node,m_map);
		}
		if(South_node!="*")
		{
			AssingNodes(Bearing::SOUTH,South_node,m_map);
		}
		if(West_node!="*")
		{
			AssingNodes(Bearing::WEST,West_node,m_map);
		}
	}	
};

class Graph
{
public:
	Graph()
	{
		if (GraphGeneration()!=0)
		{
			throw std::runtime_error("Exit");
		}		
	}
	
	~Graph()
	{	
		printf("Graph Destructor Called.\n");	
		for (auto nodes : m_map)
		{			
			delete nodes;
			nodes = nullptr;
		}
		CustomSystem::WaitForInput();
		
	}
	Graph(const Graph&) = delete;
	
	int GetTotalNodes()
	{
		return m_map.size();
	}
	Node* GetNode(int x)
	{
		return m_map[x];
	}
	Node* GetNode(std::string x)
	{
		for(unsigned int i=0;i<m_map.size();i++)
		{
			if((*m_map[i]).GetName()==x)
			{
				return m_map[i];
			}
		}
		return nullptr;
	}
private:

	std::vector<Node*> m_map;	

	int GraphGeneration()
	{
		CustomSystem::ClearScreen();
				
		std::vector<std::string>* txtMap = Parsing();
		if (txtMap!=nullptr)
		{
			for (unsigned int i = 0; i < (*txtMap).size(); i = i + 5)
			{								
				m_map.push_back(new Node((*txtMap)[i]));
			}
			
			for (size_t i = 0, x = 0; i < (*txtMap).size(); i = i + 5, x++)
			{				
				(*m_map[x]).SetBearings((*txtMap)[i + 1], (*txtMap)[i + 2], (*txtMap)[i + 3], (*txtMap)[i + 4], m_map);
			}

			delete txtMap;
			txtMap = nullptr;
			return 0;
		}
		else
		{
			return 1;
		}
	}	
	
	std::vector<std::string>* Parsing()
	{
		
		std::string input;
		bool genType=0;
		bool correctInput=false;		
		while(!correctInput)
		{			
		printf("Please select generation type.\n[R] for RNG.\n[S] for STATIC.\n[Q] to Exit.\n");
		std::cin>>input;
		if(input.size()!=1)
		{
			input="z";
		}
		if(input=="s"||input=="S")
		{
			genType=0;
			correctInput=1;
		}
		else if(input=="r"||input=="R")
		{
			genType=1;
			correctInput=1;
		}
		else if(input=="q"||input=="Q")
		{			
			throw std::runtime_error("Exit");
		}
		else
		{
			CustomSystem::ClearScreen();
			printf("Incorrect Input.\n");
		}
		
		CustomSystem::ClearScreen();
		if(genType==1&& correctInput==1)
		{

			printf("RNG not implemented yet.\n");
			CustomSystem::WaitForInput();
			throw std::runtime_error("Exit");
			
			//return randomGeneration();
		}
		else if(genType == 0 && correctInput == 1)
		{
			
			return staticGeneration();
		}		
		}
		return nullptr;
	}
	std::vector<std::string>* staticGeneration() 
	{
		bool success=false;
		CustomSystem::Directory dirObject;	
		
		std::ifstream fileObject;
		std::string input;		
		
		std::vector<std::string>* txtMap = new std::vector<std::string>();
		while (!success)
		{
			printf("Please enter the name of .txt file of map.\n");
			printf("Type 'default' for DEFAULT map.\n");
			printf("Type 'exit' to EXIT.\n");
			
			std::cin >> input;			
			
			if (input=="exit")
			{
				throw std::runtime_error("Exit");
			}
			fileObject = std::ifstream(dirObject.getDir() + "/" + input + ".txt");

			if (fileObject.is_open())
			{				
				std::vector<std::string> results;

				std::string nodeName, n, e, s, w;

				while (fileObject >> nodeName >> n >> e >> s >> w)
				{
					(*txtMap).push_back(nodeName);
					(*txtMap).push_back(n);
					(*txtMap).push_back(e);
					(*txtMap).push_back(s);
					(*txtMap).push_back(w);
				}
				fileObject.close();		
				success = true;
			}
			else
			{
				CustomSystem::ClearScreen();
				std::cout << "Cannot find file: " << dirObject.getDir() + "/" + input + ".txt" << "\n";				
			}
		}
		return txtMap;			
	}
	std::vector<std::string>* randomGeneration()
	{		
		std::vector<std::string>* txtMap = new std::vector<std::string>();
		//TODO: RNG of Graph
		return txtMap;	
	}	
};
