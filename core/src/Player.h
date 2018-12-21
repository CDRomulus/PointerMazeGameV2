#include <iostream>
class Player
{
private:
	int steps=0;
	Node* CurrentNode;
	
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
	void NavigateOptions()
	{	
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