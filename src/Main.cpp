#include <Game.hpp>

#include <stdexcept>
#include <iostream>

int main(int argc, char* argv[])
{
	try
	{
        Game game(800, 600, "SFML Game");
        game.run();
    }
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
    return 0;
}
