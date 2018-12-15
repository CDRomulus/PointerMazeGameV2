#include "Graph.h"

int main()
{
	std::vector<int> ListOne;
	printf("Hello World!");
	std::cout<<"Numbers =\n";
	ListOne.reserve(7);
	ListOne.emplace_back(1); 
	ListOne.emplace_back(2); 
	ListOne.emplace_back(3); 
	ListOne.emplace_back(4); 
	ListOne.emplace_back(5); 
	ListOne.emplace_back(6);
    ListOne.emplace_back(ListOne[3]+ListOne[5]);  
	for( unsigned int x=0; x<ListOne.size();x++)
	{
		std::cout<<ListOne[x]<<"\n";
	}
	
	std::cin.get();
}
