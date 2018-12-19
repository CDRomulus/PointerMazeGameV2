#ifndef GRAPH_H
#define GRAPH_H

#include "CustomSystem.h"

#include <vector>
#include <iostream>
#include <random>
#include <limits.h>
#include <fstream>
#include <string>
#include <stdexcept>
#include <memory>

class Node
{
	private:
	std::string m_name;
	std::vector<int> m_bearing;//0=north,1=east,2=south,3=west
	std::vector<std::shared_ptr<Node>> m_nodes;	//bearing pointer to nodes
	
	void AssingNodes(int p, std::string x,std::vector<std::shared_ptr<Node>> &m_map)
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
		//std::cout << "Node " << this->m_name << " created!\n";
	}
	~Node()
	{	
		printf("Node Destructor Called.\n");
	}

	Node(const Node&) = delete;

	std::vector<int>& GetBearings()
	{
		return m_bearing;
	}
	std::shared_ptr<Node> GetExit(int x)
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
	void SetBearings(std::string North_node, std::string East_node, std::string South_node, std::string West_node,std::vector<std::shared_ptr<Node>> &m_map)
	{
		
		if(North_node!="*")
		{
			AssingNodes(0,North_node,m_map);
		}
		if(East_node!="*")
		{
			AssingNodes(1,East_node,m_map);
		}
		if(South_node!="*")
		{
			AssingNodes(2,South_node,m_map);
		}
		if(West_node!="*")
		{
			AssingNodes(3,West_node,m_map);
		}
	}	
};

class Graph : System
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
		//printf("Graph Destructor Called.\n");			
	}
	Graph(const Graph&) = delete;
	
	int GetTotalNodes()
	{
		return m_map.size();
	}
	std::shared_ptr<Node> GetNode(int x)
	{
		return m_map[x];
	}
	std::shared_ptr<Node> GetNode(std::string x)
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

		std::vector<std::shared_ptr<Node>> m_map;

	int GraphGeneration()
	{
		
		ClearScreen();

		
		std::vector<std::string>* txtMap = Parsing();
		if (txtMap!=nullptr)
		{
			for (unsigned int i = 0; i < (*txtMap).size(); i = i + 5)
			{
				std::shared_ptr<Node> focusedNode = std::make_shared<Node>((*txtMap)[i]);
					
				m_map.push_back(focusedNode);
			}
			
			for (unsigned int i = 0, x = 0; i < (*txtMap).size(); i = i + 5, x++)
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
		bool genType;
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
			ClearScreen();
			printf("Incorrect Input.\n");
		}
		
		ClearScreen();
		if(genType==1&& correctInput==1)
		{

			printf("RNG not implemented yet.\n");
			WaitForInput();
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
		Directory dirObject;		
		std::string pathDir = dirObject.getPath();
		std::ifstream fileObject;
		std::string input;
		std::string path;
		std::string line;
		std::vector<std::string>* txtMap = new std::vector<std::string>();
		while (!success)
		{
			printf("Please enter the name of .txt file of map.\n");
			printf("Type 'default' for DEFAULT map.\n");
			printf("Type 'exit' to EXIT.\n");
			
			std::cin >> input;
			
			path = dirObject.getPath() + "/" + input + ".txt";
			if (input=="exit")
			{
				throw std::runtime_error("Exit");
			}
			fileObject = std::ifstream(path);			

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
				ClearScreen();
				std::cout << "Cannot find file: " << path << "\n";
				
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
#endif