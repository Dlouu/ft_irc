#include "Command.hpp"

void	Command::modeCommand( const CommandData_t& data ) const {
	Client	&client = *Server::getClientByFD( data.fd );
	Client	*target;
	Channel	*channel;

	std::vector<std::string> params = split( data.message, ' ' );
	g_vars[ "command" ]	= params[0];

	if (params.size() < 2) {
		return sendReply( data.fd, ERR_NEEDMOREPARAMS );
	} else if (params.size() >= 2 && params[1] == client.getNickname()) {
		if (params.size() == 2) {
			g_vars[ "modes" ]	= "+i";
			return sendReply( data.fd, RPL_UMODEIS );
		} else if (params.size() == 3 && params[2] == "+i") {
			return sendMessage( data.fd, ":{server} :{mask} MODE {nick} :+i" );
		} else {
			return ;
		}
	} else {
		channel = Server::getChannel( params[1] );
		if (channel) {
			g_vars[ "channel" ]	= channel->getName();
			if (!channel->isClientUser( client )) {
				return sendReply( data.fd, ERR_NOTONCHANNEL );
			}
			if (params.size() == 2 && params[1] == channel->getName()) {
				g_vars[ "channel" ]	= params[1];
				g_vars[ "modes" ]	= channel->getChannelModes();
				g_vars[ "params" ]	= channel->getChannelParams();
				return sendReply( data.fd, RPL_CHANNELMODEIS );
			}
		} else {
			g_vars[ "channel" ]	= params[1];
			return sendReply( data.fd, ERR_NOSUCHCHANNEL );
		}
	}

	const std::string			modeString = params[2];
	std::string					flagsApplied;
	char						sign = '+';
	size_t						paramIdx = 3;
	std::vector<std::string>	usedParams;

	for (size_t i = 0; i < modeString.size(); ++i) {
		char c = modeString[i];
		if (c == 'b')
			return ;
		if (c == '+' || c == '-') {
			sign = c;
			flagsApplied += c;
			continue;
		}

	if (!channel->isClientOperator( client )) {
		sendReply( data.fd, ERR_CHANOPRIVSNEEDED );
	} else {
		switch (c) {
			case 'i':
				channel->setInviteOnly(sign == '+');
				flagsApplied += 'i';
				break;

			case 't':
				channel->setTopicRestricted(sign == '+');
				flagsApplied += 't';
				break;

			case 'k':
				if (sign == '+') {
					if (paramIdx >= params.size())
						return sendReply( data.fd, ERR_NEEDMOREPARAMS );
					std::string key = params[paramIdx];
					paramIdx++;
					if (channel->getPassword() == key)
						return sendReply( data.fd, ERR_KEYSET );
					if (key == "x")
						return sendMessage( data.fd, ":{server} :{mask} Invalid key for irssi" );
					channel->setPassword( key );
					usedParams.push_back( key );
				} else if (sign == '-') {
					channel->setPassword("");
				}
				flagsApplied += 'k';
				break;

			case 'o':
				if (paramIdx >= params.size()) {
					return sendReply( data.fd, ERR_NEEDMOREPARAMS );
				}
				target = Server::getClientByNick( params[paramIdx] );
				paramIdx++;
				if (!channel->isClientUser( *target )) {
					return sendReply( data.fd, ERR_NOTONCHANNEL );
				}
				if (sign == '+') {
					channel->addOperator( *target );
				} else if (sign == '-') {
					channel->delOperator( *target );
					usedParams.push_back( target->getNickname() );
				}
				flagsApplied += 'o';
				break;

			case 'l':
				if (sign == '+') {
					if (paramIdx >= params.size())
						return sendReply( data.fd, ERR_NEEDMOREPARAMS);
					std::string limit = params[paramIdx];
					paramIdx++;
					channel->setUserLimit(std::atoll( limit.c_str() ));
					usedParams.push_back(limit);
				} else if (sign == '-') {
					channel->setUserLimit(0);
				}
				flagsApplied += 'l';
				break;

			default:
				return sendReply( data.fd, ERR_UMODEUNKNOWNFLAG );
			}

			std::ostringstream oss;
			oss << flagsApplied;
			for (size_t i = 0; i < usedParams.size(); ++i) {
				oss << " " << usedParams[i];
			}
			channel->shareMessage( client, oss.str(), "MODE" );
		}
	}
}
