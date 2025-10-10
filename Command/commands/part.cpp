#include "Command.hpp"

static void	isItGood(std::string chan, std::string lastWord, int fd) {
	Server *instance = Server::getInstance();
	if (!instance)
		return;
	std::string mask = instance->getClientByFD(fd)->getMask();
	if (!instance->getChannel(chan)->isClientUser(*instance->getClientByFD(fd))) {
		sendReply(fd, ERR_NOTONCHANNEL);
		return;
	}
	std::string msg = ":" + mask + " PART " + chan + " " + lastWord + "\r\n";

	instance->getChannel(chan)->shareMessage(msg);	//shareMessage(user PART #*it lasword);
	g_vars[ "channel" ] = instance->getChannel(chan)->getName();
	sendMessage( fd, ":" + mask + " KICK {channel} {nick} :{reason}" );
	instance->getChannel(chan)->delUser(*instance->getClientByFD(fd));
}

void	Command::partCommand(const CommandData_t& data) const {
	std::string lastWord;
	std::string raw = data.message.substr(5, data.message.length());

	std::vector< std::string > chansData = this->split( raw, ' ' );
	std::vector< std::string > chans = this->split( chansData[ 0 ], ',' );

	if (chansData.size() > 1) {
		for (size_t i = 1; i < chansData.size(); ++i) {
			lastWord += chansData[i];
		}
	}
	for (std::vector<std::string>::iterator it = chans.begin(); it != chans.end(); ++it) {
		if (Server::getInstance()->DoesChannelExist(*it)) {
			isItGood(*it, lastWord, data.fd);
		} else if (!Server::getInstance()->DoesChannelExist(*it)) {
			sendReply(data.fd, ERR_NOSUCHCHANNEL);
		}
	}
}

/* Numeric Replies:

           ERR_NEEDMOREPARAMS (irssi check en amont)
		    */
