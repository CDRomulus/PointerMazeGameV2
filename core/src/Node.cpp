#include "Map.h"

void Node::AssingNodes(Bearing p, const std::string x, std::vector<Node*> &m_map)
{
	for (unsigned int i = 0; i < m_map.size(); i++)
	{
		if ((*m_map[i]).GetName() == x)
		{
			m_bearing.push_back(p);
			m_nodes.push_back(m_map[i]);
			break;
		}
	}
}

Node::Node(std::string name)
{
	this->m_name = name;
}
Node::~Node()
{
	std::cout << "Node Destructor Called: " << m_name << "\n";
	for (unsigned int x = 0; x < m_nodes.size(); x++)
	{
		m_nodes[x] = nullptr;
	}

}



const std::vector<Bearing>& Node::GetAvailableBearings()
{
	return m_bearing;
}
Node* Node::GetExit(Bearing x)
{
	for (unsigned int i = 0; i < m_bearing.size(); i++)
	{
		if (m_bearing[i] == x)
		{
			return m_nodes[i];
		}
	}
	return nullptr;
}

std::string Node::GetName()
{
	return m_name;
}
void Node::SetBearings(std::string North_node, std::string East_node, std::string South_node, const std::string West_node, std::vector<Node*> &m_map)
{

	if (North_node != "*" || North_node != "")
	{
		AssingNodes(Bearing::NORTH, North_node, m_map);
	}
	if (East_node != "*" || East_node != "")
	{
		AssingNodes(Bearing::EAST, East_node, m_map);
	}
	if (South_node != "*" || South_node != "")
	{
		AssingNodes(Bearing::SOUTH, South_node, m_map);
	}
	if (West_node != "*" || West_node != "")
	{
		AssingNodes(Bearing::WEST, West_node, m_map);
	}
}
void Node::setTreasure()
{
	m_treasure = TRUE;
}
bool Node::getTreasureBool()
{
	return m_treasure;
}