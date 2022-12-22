#include <iostream>
#include <memory>

#include "ShmupGame.h"


int main(int argc, char ** argv)
{
	
	std::unique_ptr<SHMUPGame> game = std::make_unique<SHMUPGame>();
	game->Init();
	game->Run();
	
	return 0;
}