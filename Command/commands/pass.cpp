#include "Command.hpp"

void	Command::passCommand(const CommandData_t& data) const {
	std::string pass = data.message.substr(5, data.message.length());

	if (Server::isClientRegistered( data.fd ))
		return sendReply( data.fd, ERR_ALREADYREGISTRED );
	if (pass.empty())
		return sendReply(data.fd, ERR_NEEDMOREPARAMS);
	else if (pass == Server::getInstance()->getServPass())
		Server::setPassByFD(data.fd, true);
}
