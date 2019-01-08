#include "Graph.h"
#include "Player.h"


bool CheckAndExecute(Player& player,const Bearing x)
{
	
	for(unsigned int i=0; i<player.GetCurrentNode()->GetAvailableBearings().size();i++)
	{
		if(player.GetCurrentNode()->GetAvailableBearings()[i]==x)
		{
			player.SetCurrentNode(player.GetCurrentNode()->GetExit(x));
			player.SetSteps();
			return 1;
		}
	}
	return 0;
}

int main()//loop check when exited
{
	try {

		Graph graph;				

		int totalNodes = graph.GetTotalNodes();
		int random_integer= CustomSystem::rngIntGen(totalNodes-4, totalNodes);
		Node* endgameNode = graph.GetNode(random_integer-1);

		Player player(graph.GetNode(0));//Get first Node

		CustomSystem::ClearScreen();
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
			if ((input == "n" || input == "N") && CheckAndExecute(player, Bearing::NORTH))
			{					
			}
			else if ((input == "e" || input == "E") && CheckAndExecute(player, Bearing::EAST))
			{				
			}
			else if ((input == "s" || input == "S") && CheckAndExecute(player, Bearing::SOUTH))
			{					
			}
			else if ((input == "w" || input == "W") && CheckAndExecute(player, Bearing::WEST))
			{					
			}
			else if (input == "q" || input == "Q")
			{
				CustomSystem::ClearScreen();
				std::cout << "Current Node: " << player.GetCurrentNode()->GetName() <<"\n";
				std::cout << "End Node: " << endgameNode->GetName() << "\n";
				std::cout << "Total Steps: " << player.GetSteps() <<"\n";	
				
				
				throw std::runtime_error("Exit");
			}
			else
			{
				check = false;
			}

			CustomSystem::ClearScreen();
		}
		CustomSystem::ClearScreen();
		std::cout << "You found Node: " << endgameNode->GetName() << "!" << std::endl;
		std::cout << "Total Steps: " << player.GetSteps() << "\n";			
	}	
	catch (const std::exception& e) 
	{
		std::string ex = e.what();
		if (ex == "Exit")
		{
			e.~exception();
			std::cout << "\nPress enter to exit.";
			CustomSystem::WaitForInput();
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
