#include "Server.hpp"

std::map<int, std::string> g_replies;
std::map<std::string, std::string> g_vars;

// si j'invite quelqu'un depuis le channel, le message d'erreur ferme le channel cote client alors
// qu'il existe toujours cote serveur

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);

	catch_sig();
	int port = atoi(argv[1]);
	std::string password = argv[2];

	Server::getInstance()->init(port, password);
	Server::getInstance()->loop();

	Server::destroyInstance();
	return (0);
}
