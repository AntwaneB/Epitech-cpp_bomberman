#include <iostream>
#include "Core/App.hh"
#include "Exception.hpp"

int	main(int ac, char **av)
{
	srand(time(NULL));

	App*	app = NULL;
	try
	{
		app = new App(ac, av);

		int ret = app->run();
		delete app;

		return (ret);
	} catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;

		return (0);
	}
}
