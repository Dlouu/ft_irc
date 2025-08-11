#include "Server/Server.hpp"

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);

	catch_sig();

	int port = atoi(argv[1]);
	std::string password = argv[2];

	Server::GetInstance()->init(port);

	//Server::GetInstance()->loop();

	//Server::DestroyInstance();
	Server *s = Server::GetInstance();
	delete s;
	return (EXIT_SUCCESS);
}
