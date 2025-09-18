#include "Command.hpp"



void	Command::quitCommand( const CommandData_t& data ) const {
	Server *instance = Server::getInstance();
	Client *user = instance->getClientByFD(data.fd);
	std::vector<std::string> chans = user->getChannels();
	std::vector<std::string> msg = split(data.message, ':');

	for (std::vector<std::string>::iterator it = chans.begin(); it != chans.end(); ++it) {
		instance->getChannel(*it)->delUser(*user);
		instance->getChannel(*it)->shareMessage(":" + user->getMask() + " QUIT :" + msg[1] + "\r\n");
	}
	instance->delClient(data.fd);
}
