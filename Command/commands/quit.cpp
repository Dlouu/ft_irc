#include "Command.hpp"

void	Command::quitCommand( const CommandData_t& data ) const {
	Server *instance = Server::getInstance();
	Client *user = instance->getClientByFD(data.fd);
	std::vector<std::string> chans = user->getChannels();

	for (std::vector<std::string>::iterator it = chans.begin(); it != chans.end(); ++it) {
		instance->getChannel(*it)->shareMessage()
		instance->getChannel(*it)->delUser(*user);

	}
}