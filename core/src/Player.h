#include <iostream>
class Player
{
private:
	int steps=0;
	std::shared_ptr<Node> CurrentNode;
	
public:
	Player(std::shared_ptr<Node> x)
	{
		CurrentNode =x; 
	}	
	
	std::shared_ptr<Node> GetCurrentNode()
	{
		return CurrentNode;
	}
	
	void SetCurrentNode(std::shared_ptr<Node> x)
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
		std::vector<int>& bearing = CurrentNode->GetBearings();
		for(unsigned int i=0; i<bearing.size();i++)
		{
			
			if(bearing[i]==0)
			{
				std::cout<<" [N]orth,";
			}
			else if(bearing[i]==1)
			{
				std::cout<<" [E]ast,";
			}
			else if(bearing[i]==2)
			{
				std::cout<<" [S]outh,";
			}
			else if(bearing[i]==3)
			{
				std::cout<<" [W]est,";
			}			
		}
		std::cout<<"\n[Q]uit.\n";		
	}
};