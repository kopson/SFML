#include <Application.hpp>

#include <stdexcept>
#include <iostream>

int main(int argc, char* argv[])
{
	try
	{
        Application app;
		app.run();
    }
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
    return 0;
}
