#include "Command.hpp"

static void	isItGood(std::string chan, std::string lastWord, int fd) {
	Channel	*channel = Server::getChannel(chan);
	if (!channel)
		return sendReply(fd, ERR_NOSUCHCHANNEL);
	Client	*client = Server::getClientByFD(fd);
	if (!client || !channel->isClientUser(*client))
		return sendReply(fd, ERR_NOTONCHANNEL);

	g_vars[ "reason" ] = lastWord;
	g_vars[ "channel" ] = channel->getName();
	channel->delUser(*client);
}

void	Command::partCommand(const CommandData_t& data) const {
	std::string lastWord;
	size_t		lastWordPos	= 0;

	std::string raw = data.message.substr(5, data.message.length());

	if ((lastWordPos = data.message.find(":")) != std::string::npos)
		lastWord = data.message.substr( lastWordPos, data.message.length() - lastWordPos );

	std::vector< std::string > chansData = this->split( raw, ' ' );
	std::vector< std::string > chans = this->split( chansData[ 0 ], ',' );

	for (std::vector<std::string>::iterator it = chans.begin(); it != chans.end(); ++it) {
		if (Server::getInstance()->DoesChannelExist(*it)) {
			isItGood(*it, lastWord, data.fd);
		} else if (!Server::getInstance()->DoesChannelExist(*it)) {
			sendReply(data.fd, ERR_NOSUCHCHANNEL);
		}
	}
}
