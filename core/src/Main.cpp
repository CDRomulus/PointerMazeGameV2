#include "Graph.h"
#include "Player.h"
#include <stdio.h>

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
int rngIntGen(int l_thresh, int h_thresh)
{
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(l_thresh, h_thresh); // guaranteed unbiased
	auto random_integer = uni(rng);
	return random_integer;
}
int main()//loop check when exited
{
	try {

		Graph graph;
		System system;

		int totalNodes = graph.GetTotalNodes();
		int random_integer=rngIntGen(totalNodes-4, totalNodes);
		std::shared_ptr<Node> endgameNode = graph.GetNode(random_integer-1);

		Player player(graph.GetNode(0));

		system.ClearScreen();
		bool check=true;
		std::string input;

		while (player.GetCurrentNode() != endgameNode)
		{		

			std::cout << "Find Node: " << endgameNode->GetName() << "\n";
			player.NavigateOptions();
			if (check==false)
			{
				printf("Please enter a correct input!\n");
			}
			check = true;

			input="";			
			std::cin>>input;
			if(input.size()!=1)
			{
			input="z";
			}			
			if ((input == "n" || input == "N") && CheckBearingExists(player.GetCurrentNode()->GetBearings(), 0))
			{			
				player.SetCurrentNode(player.GetCurrentNode()->GetExit(0));
				player.SetSteps();
			}
			else if ((input == "e" || input == "E") && CheckBearingExists(player.GetCurrentNode()->GetBearings(), 1))
			{			
				player.SetCurrentNode(player.GetCurrentNode()->GetExit(1));
				player.SetSteps();
			}
			else if ((input == "s" || input == "S") && CheckBearingExists(player.GetCurrentNode()->GetBearings(), 2))
			{			
				player.SetCurrentNode(player.GetCurrentNode()->GetExit(2));
				player.SetSteps();
			}

			else if ((input == "w" || input == "W") && CheckBearingExists(player.GetCurrentNode()->GetBearings(), 3))
			{				
				player.SetCurrentNode(player.GetCurrentNode()->GetExit(3));
				player.SetSteps();
			}
			else if (input == "q" || input == "Q")
			{
				system.ClearScreen();
				std::cout << "Current Node: " << player.GetCurrentNode()->GetName() <<"\n";
				std::cout << "End Node: " << endgameNode->GetName() << "\n";
				std::cout << "Total Steps: " << player.GetSteps() <<"\n";	
				
				system.WaitForInput();
				throw std::runtime_error("Exit");
			}
			else
			{
				check = false;
			}

			system.ClearScreen();
		}
		system.ClearScreen();
		std::cout << "You found Node: " << endgameNode->GetName() << "!" << std::endl;
		std::cout << "Total Steps: " << player.GetSteps() << "\n";	
		system.WaitForInput();
	}	
	catch (const std::exception& e)
	{
		std::string ex = e.what();
		if (ex == "Exit")
		{
			return 0;
		}
		else
		{
			std::cout << "Exeption: " << e.what()<<"\n";
			return 1;			
		}
	}
	return 0;	
}
