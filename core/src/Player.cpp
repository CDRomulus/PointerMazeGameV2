#pragma once

#include <iostream>

class Player
{
private:
	int steps=0;
	Node* CurrentNode;
	std::vector<Node*> treasureList;

	bool treasureObtained()
	{
		if (treasureList.size() == 0)
		{
			return FALSE;
		}
		else
		{
			for (unsigned int i =0; i < treasureList.size(); i++)
			{
				if (treasureList[i]==CurrentNode)
				{
					return TRUE;
				}
			}
			return FALSE;
		}		
	}
public:
	Player(Node* x)
	{
		CurrentNode =x;
	}

	Node* GetCurrentNode()
	{
		return CurrentNode;
	}

	void SetCurrentNode(Node* x)
	{
		CurrentNode =x;
	}
	void SetSteps()
	{
		steps++;
	}
	int GetSteps()
	{
		return steps;
	}
	int getTreasureCount()
	{
		return static_cast<int>(treasureList.size());
	}
	void NavigateOptions()
	{
		if (treasureObtained()==FALSE&&(*CurrentNode).getTreasureBool()==TRUE)
		{
			std::cout << "YOU FOUND THE TREASURE!\n\n";
			treasureList.emplace_back(CurrentNode);
		}
		std::cout<<"Total Steps: "<< GetSteps()<<"\n";
		std::cout<<"You are at Node: "<< CurrentNode->GetName()<<std::endl;

		std::cout<<"You can go:";
		const std::vector<Bearing>& availableBearings = CurrentNode->GetAvailableBearings();
		for(unsigned int i=0; i<availableBearings.size();i++)
		{

			if(availableBearings[i]==Bearing::NORTH)
			{
				std::cout<<" [N]orth,";
			}
			else if(availableBearings[i]== Bearing::EAST)
			{
				std::cout<<" [E]ast,";
			}
			else if(availableBearings[i]== Bearing::SOUTH)
			{
				std::cout<<" [S]outh,";
			}
			else if(availableBearings[i]== Bearing::WEST)
			{
				std::cout<<" [W]est,";
			}
		}
		std::cout<<"\n[Q]uit.\n";
	}
};
