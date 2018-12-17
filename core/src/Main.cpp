#include "Graph.h"
#include "Player.h"

bool CheckBearingExists(std::vector<int>& bearing,int exit)
{
	for(unsigned int i=0; i<bearing.size();i++)
	{
		if(bearing[i]==exit)
		{
			return 1;
		}
	}
	return 0;
}
int main()
{
	Graph graph;	
	
	int totalNodes = graph.GetTotalNodes();
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(totalNodes-4,totalNodes); // guaranteed unbiased
	auto random_integer = uni(rng);
	
	Node* endgameNode = graph.GetNode(random_integer);
	
	Player player(graph.GetNode(0));
	while(player.GetCurrentNode()!=endgameNode)
	{
		system("clear");
		std::cout<<"Find Node: "<<endgameNode->GetName()<<"\n";
		player.NavigateOptions();
		
		char input=getchar();
		std::cin>>input;	
		
			if((input=='n'||input=='N')&&CheckBearingExists(player.GetCurrentNode()->GetBearings(),0))
			{				
				player.SetCurrentNode(player.GetCurrentNode()->GetExit(0));
				player.SetSteps();
							
			}
			else if((input=='e'||input=='E')&&CheckBearingExists(player.GetCurrentNode()->GetBearings(),1))
			{
				player.SetCurrentNode(player.GetCurrentNode()->GetExit(1));
				player.SetSteps();		
		
			}
			else if((input=='s'||input=='S')&&CheckBearingExists(player.GetCurrentNode()->GetBearings(),2))
			{
				player.SetCurrentNode(player.GetCurrentNode()->GetExit(2));
				player.SetSteps();
			}
		
			else if((input=='w'||input=='W')&&CheckBearingExists(player.GetCurrentNode()->GetBearings(),3))
			{
				player.SetCurrentNode(player.GetCurrentNode()->GetExit(3));	
				player.SetSteps();
			}
			else
			{
				system("clear");		
				std::cout<<input<<"\n";
				printf("Please select a correct input!");
			}		
	}
	system("clear");
	std::cout<<"You found Node: "<<endgameNode->GetName()<<"!"<<std::endl;
	std::cout<<"Total Steps: "<<player.GetSteps()<<"\n";
	return 0;
}

