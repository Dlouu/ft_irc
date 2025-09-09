#include "Command.hpp"

static void	isItGood(std::string chan, std::string lastWord, int fd) {
	if (!Server::getInstance()->getChannel(chan)->isClientUser(*Server::getInstance()->getClientByFD(fd))) {
		std::cout << "client no on channel [" << chan << "]\n";
		//ERR_NOTONCHANNEL
		return;
	}
	std::cout << "message [" << lastWord << "] shared to channel(s)\n";
	//shareMessage(user PART #*it lasword);
}

void	Command::partCommand(const CommandData_t& data) const {
	std::string lastWord;
	std::string raw = data.message.substr(5, data.message.length());

	std::cout << "["<< raw << "]\n";

	std::vector< std::string > chansData = this->split( raw, ' ' );
	std::vector< std::string > chans = this->split( chansData[ 0 ], ',' );
	
	if (chansData.size() > 1) {
		for (size_t i = 1; i < chansData.size(); ++i) {
			lastWord += chansData[i];
		}
	}
	for (std::vector<std::string>::iterator it = chans.begin(); it != chans.end(); ++it) {
		if (Server::getInstance()->isChannelExist(*it)) {
			isItGood(*it, lastWord, data.fd);
		} else if (!Server::getInstance()->isChannelExist(*it)) {
			std::cout << "channel [" << *it << " ]not found\n";
			//ERR_NOSUCHCHANNEL
		}
	}
}

/* Numeric Replies:

           ERR_NEEDMOREPARAMS (irssi check en amont)
		    */