#include "Server/Server.hpp"

std::map<int, std::string> g_replies;
std::map<std::string, std::string> g_vars;

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);

	catch_sig();

	int port = atoi(argv[1]);
	std::string password = argv[2];

	Server::GetInstance()->init(port);
	Server::GetInstance()->loop();

	return (EXIT_SUCCESS);
}
