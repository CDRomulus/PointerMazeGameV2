#include "Map.h"

	bool Player::treasureObtained()
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

	Player::Player(Node* x)
	{
		CurrentNode =x;
	}

	Node* Player::GetCurrentNode()
	{
		return CurrentNode;
	}

	void Player::SetCurrentNode(Node* x)
	{
		CurrentNode =x;
	}
	void Player::SetSteps()
	{
		steps++;
	}
	int Player::GetSteps()
	{
		return steps;
	}
	int Player::getTreasureCount()
	{
		return static_cast<int>(treasureList.size());
	}
	void Player::NavigateOptions()
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

