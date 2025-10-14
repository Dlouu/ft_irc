#include "Command.hpp"

void	Command::quitCommand( const CommandData_t& data ) const {
	Client *user = Server::getClientByFD(data.fd);
	if (!user)
		return;
	std::vector<std::string> chans = user->getChannels();
	std::vector<std::string> msg = split(data.message, ':');
	if (chans.empty())
		return;
	for (std::vector<std::string>::iterator it = chans.begin(); it != chans.end(); ++it) {
		if (!Server::DoesChannelExist(*it)) {
			g_vars[ "channel" ] = *it;
			sendReply(user->getFD(), ERR_NOSUCHCHANNEL);
			continue;
		}
		Server::getChannel(*it)->shareMessage(":" + user->getMask() + " QUIT :" + msg[1] + "\r\n");
		Server::getChannel(*it)->delUser(*user);
	}
	Server::delClient(data.fd);
}
