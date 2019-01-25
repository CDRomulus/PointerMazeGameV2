#include "Graph.cpp"
#include "Player.cpp"


bool CheckAndExecute(Player& player,const Bearing x)
{

	for(unsigned int i=0; i<player.GetCurrentNode()->GetAvailableBearings().size();i++)
	{
		if(player.GetCurrentNode()->GetAvailableBearings()[i]==x)
		{
			player.SetCurrentNode(player.GetCurrentNode()->GetExit(x));
			player.SetSteps();
			return TRUE;
		}
	}
	return 0;
}

int main()
{
	try {

		Graph mainGraph;	

		Player player(mainGraph.GetNode(0));//Set player on first node

		CustomSystem::ClearScreen();
		bool check=true;
		std::string input;
		
		while (player.GetCurrentNode() != mainGraph.getEndGameNode())
		{

			std::cout << "Find Node: " << mainGraph.getEndGameNode()->GetName() << "\n";
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
				std::cout << "End Node: " << mainGraph.getEndGameNode()->GetName() << "\n";
				std::cout << "Total Steps: " << player.GetSteps() <<"\n";


				throw std::runtime_error("Exit");
			}
			else
			{
				check = false;
			}

			CustomSystem::ClearScreen();
		}

	int points = 50 -player.GetSteps() + (player.getTreasureCount() *30); //TREASURE POINT MULTIPLYER FOR LEADERBOARD
    CustomSystem::ClearScreen();
	std::cout << "YOU HAVE ESCAPED AT NODE: " << mainGraph.getEndGameNode()->GetName() << "!" << std::endl;

	std::cout << "TOTAL STEPS: " << player.GetSteps() << "\n";
	std::cout << "TOTAL SCORE = " <<points<< std::endl;

	std::cout << "PLEASE ENTER YOUR NAME." << std::endl;

	std::string leaderBoardName;
	std::cin >> leaderBoardName;

	if (leaderBoardName !="")
	{
		std::ofstream fStreamObject;
		
		fStreamObject.open(CustomSystem::GetDirectory() + "/" + mainGraph.getFileName() + "_Leaderboard.txt", std::ios::app);

		fStreamObject << std::endl;

		fStreamObject <<"NAME = "<< leaderBoardName;

		fStreamObject << "--TREASURE_FOUND = " << (player.getTreasureCount());

		fStreamObject <<"--POINTS = "<< points;

		fStreamObject.close();
}
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
