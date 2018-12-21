#include "Graph.h"
#include "Player.h"


bool CheckBearingExists(const std::vector<Bearing>& bea,Bearing x)
{
	for(unsigned int i=0; i<bea.size();i++)
	{
		if(bea[i]==x)
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

		int totalNodes = graph.GetTotalNodes();
		int random_integer=rngIntGen(totalNodes-4, totalNodes);
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
			if ((input == "n" || input == "N") && CheckBearingExists(player.GetCurrentNode()->GetAvailableBearings(), Bearing::NORTH))
			{			
				player.SetCurrentNode(player.GetCurrentNode()->GetExit(Bearing::NORTH));
				player.SetSteps();
			}
			else if ((input == "e" || input == "E") && CheckBearingExists(player.GetCurrentNode()->GetAvailableBearings(), Bearing::EAST))
			{			
				player.SetCurrentNode(player.GetCurrentNode()->GetExit(Bearing::EAST));
				player.SetSteps();
			}
			else if ((input == "s" || input == "S") && CheckBearingExists(player.GetCurrentNode()->GetAvailableBearings(), Bearing::SOUTH))
			{			
				player.SetCurrentNode(player.GetCurrentNode()->GetExit(Bearing::SOUTH));
				player.SetSteps();
			}

			else if ((input == "w" || input == "W") && CheckBearingExists(player.GetCurrentNode()->GetAvailableBearings(), Bearing::WEST))
			{				
				player.SetCurrentNode(player.GetCurrentNode()->GetExit(Bearing::WEST));
				player.SetSteps();
			}
			else if (input == "q" || input == "Q")
			{
				CustomSystem::ClearScreen();
				std::cout << "Current Node: " << player.GetCurrentNode()->GetName() <<"\n";
				std::cout << "End Node: " << endgameNode->GetName() << "\n";
				std::cout << "Total Steps: " << player.GetSteps() <<"\n";	
				
				CustomSystem::WaitForInput();
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
