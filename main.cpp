#include "Server.hpp"

std::map<int, std::string> g_replies;
std::map<std::string, std::string> g_vars;

// MODIFIER LA MANIERE DONT LE CHANNEL EST SUPPRIME SI IL N'Y A PLUS D'UTILISATEUR
// CAR ACTUELLEMENT CONTROLLER CE TRUC VIA LE DELUSER DU SERVEUR PEUT CREER DES SEGFAULT
// ET DES INVQLIDES READ EN FONCTION DE COMMENT LE CODE EST FAIT

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);

	DISABLE_DEBUG();
	catch_sig();
	int port = atoi(argv[1]);
	std::string password = argv[2];

	Server::getInstance()->init(port, password);
	Server::getInstance()->loop();

	Server::destroyInstance();
	return (0);
}
