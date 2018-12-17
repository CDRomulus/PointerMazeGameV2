#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <random>
#include <limits.h>
#include <unistd.h>
#include <fstream>

class System
{
	protected:
	std::string GetExeFileName()
	{
		char result[ PATH_MAX ];
		ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
		return std::string( result, (count > 0) ? count : 0 );
		
	}
	std::string GetExePath()
	{
		std::string f = GetExeFileName();
		return f.substr(0, f.find_last_of("\\/"));
	}	
	void ClearScreen()
    {
    system("clear");
    }

};
class Node
{
	private:
	std::string m_name;
	std::vector<int> m_bearing;//0=north,1=east,2=south,3=west
	std::vector<Node*> m_nodes;	//bearing pointer to nodes
	
	void AssingNodes(int p, std::string x,std::vector<Node*> &m_map)
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
			
	}
	std::vector<int>& GetBearings()
	{
		return m_bearing;
	}
	Node* GetExit(int x)
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
	//return 2d vector of bearing and node*
	std::string GetName()
	{
		return m_name;
	}
	void SetBearings(std::string North_node, std::string East_node, std::string South_node, std::string West_node,std::vector<Node*> &m_map)
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
	std::vector<Node*> m_map;
	
	public:
	Graph()
	{
		GraphGeneration();		
	}
	
	~Graph()
	{		
		for(unsigned i =0; i<m_map.size();i++)
		{						
			delete m_map[i];				
			m_map[i] = nullptr;				
		}	
	}
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
	void GraphGeneration()
	{
		ClearScreen();
		
		std::vector<std::string>* txtMap = Parsing();
		
		for(unsigned int i=0; i <(*txtMap).size(); i=i+5)
		{
			Node* focusedNode = new Node((*txtMap)[i]);	
			m_map.push_back(focusedNode);
		}
		for(unsigned int i=0,x=0; i <(*txtMap).size(); i=i+5, x++)
		{
			
			(*m_map[x]).SetBearings((*txtMap)[i+1],(*txtMap)[i+2],(*txtMap)[i+3],(*txtMap)[i+4],m_map);
		}
		
		delete txtMap;	
		txtMap = nullptr;			
			
	}	
	
	std::vector<std::string>* Parsing()
	{
		std::vector<std::string>* txtMap;
		int input;
		bool genType;
		bool correctInput=false;		
		while(!correctInput)
		{
			
		printf("Please select generation type.\n'R' for RNG.\n'S' for STATIC.\n");
		input=getchar();		
		if(input==83||input==115)
		{
			genType=0;
			correctInput=1;
		}
		else if(input==82||input==114)
		{
			genType=1;
			correctInput=1;
		}
		else if(input==81||input==113)
		{			
			exit(0);
		}
		else
		{	ClearScreen();
			printf("Incorrect Input.\n");
		}
		}
		ClearScreen();
		if(genType==1)
		{
			txtMap = randomGeneration();
		}
		else 
		{
			txtMap = staticGeneration();
		}		
		return txtMap;
	}
	std::vector<std::string>* staticGeneration()
	{
		std::vector<std::string>* txtMap = new std::vector<std::string>();	
		printf("Please enter the name of .txt file of map.\n");
		printf("Type default for DEFAULT included map.\n");
		std::string input;
		std::cin>>input;
		std::string path = GetExePath()+"/"+input+".txt";
		
		std::ifstream fileObject(path);
		std::string line;
		
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
		}
		else
		{
			
			std::cout<<path<<"\n";
			std::cout<<"File Not found!\n";
			exit(0);
		}	
		for(unsigned int i=0; i<(*txtMap).size();i=i+5)
		{
			
		}		
		
		return txtMap;
	}
	std::vector<std::string>* randomGeneration()
	{
		std::vector<std::string>* txtMap = new std::vector<std::string>();		
		
		printf("RNG gen!\n");
		return txtMap;
	}	
};
#endif