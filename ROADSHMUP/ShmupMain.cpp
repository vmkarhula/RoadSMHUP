#include <iostream>
#include <memory>
#include <filesystem>

#include "ShmupGame.h"


int main(int argc, char ** argv)
{
	
	std::cout << "RoadSHMUP launching" << std::endl;
	std::cout << "Current workign directory" 
	<<  std::filesystem::current_path() << std::endl;


	std::unique_ptr<SHMUPGame> game = std::make_unique<SHMUPGame>();
	game->Init();
	game->Run();
	
	return 0;
}