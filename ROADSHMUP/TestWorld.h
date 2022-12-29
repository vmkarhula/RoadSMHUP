#include "SHMUPWorld.h"
#include <filesystem>

class TestWorld: public SHMUPWorld
{
    TestWorld();
    TestWorld(std::filesystem::path configurationPath, int seed);
    
    ~TestWorld();

    

}