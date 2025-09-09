#include "Command.hpp"

void	Command::modeCommand( const CommandData_t& data ) const {
	Client &client = *Server::getClientByFD( data.fd );
	Server	*server = Server::getInstance();
	Channel	*channel;
	std::vector<std::string> params = split( data.message, ' ' );
	g_vars[ "command" ]	= params[0];

	if (params.size() < 2) {
		return sendReply( data.fd, ERR_NEEDMOREPARAMS );
	} else if (params.size() == 3 && params[1] == client.getNickname() && params[2] == "+i") {
		return (sendMessage( data.fd, ":{server} :{nick}!{user}@{host} MODE {nick} :+i" ));
	} else {
		channel = server->getChannel( params[1] );
		if (!channel->getName().empty()) {
			g_vars[ "channel" ]	= channel->getName();
			if (!channel->isClientUser( client )) {
				return sendReply( data.fd, ERR_NOTONCHANNEL );
			}
			if (params.size() == 2) {
				if (params[1] == channel->getName()) {
					g_vars[ "channel" ]	= params[1];
					g_vars[ "modes" ]	= channel->getChannelModes();
					g_vars[ "params" ]	= channel->getChannelParams();
					return sendReply( data.fd, RPL_CHANNELMODEIS );
				} else if (params[1] == client.getNickname()) {
					g_vars[ "modes" ]	= "+i";
					return sendReply( data.fd, RPL_UMODEIS );
				}
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
		if (c == '+' || c == '-') {
			sign = c;
			flagsApplied += c;
			continue;
		}
	
	if (!channel->isClientOperator( client )) {
		return sendReply( data.fd, ERR_CHANOPRIVSNEEDED );
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
					channel->setPassword( key );
					usedParams.push_back( key );
				} else {
					channel->setPassword("");
				}
				flagsApplied += 'k';
				break;

			case 'o':
			// if (paramIdx >= params.size())
			// 	return sendReply(client, ERR_NEEDMOREPARAMS);
			// {
			// besoin d'un GetClientByNick je pense
			// 	std::string targetNick = params[paramIdx++];
			// 	if (!channel->isClientUser(targetNick))
			// 		return sendReply(client, ERR_NOTONCHANNEL);
			// 	if (sign == '+')
			// 		channel.promoteOp(targetNick);
			// 	else
			// 		channel.demoteOp(targetNick);
			// 	usedParams.push_back(targetNick);
			// }
				std::cout << "Give/take operator privilege to -target- " << (sign == '+' ? "on" : "off") << std::endl;
				flagsApplied += 'o';
				if (sign == '+') {
					std::cout << "Promoting user to OP:" << std::endl;
				} else if (sign == '-') {
					std::cout << "Demoting user from OP:" << std::endl;
				}
				if (params.size() > paramIdx) {
					std::cout << params[paramIdx] << std::endl;
					paramIdx++;
				} else {
					return sendReply( data.fd, ERR_NEEDMOREPARAMS );
				}
				break;

			case 'l':
				if (sign == '+') {
					if (paramIdx >= params.size())
						return sendReply( data.fd, ERR_NEEDMOREPARAMS);
					std::string limit = params[paramIdx];
					paramIdx++;
					channel->setUserLimit(std::atoll( limit.c_str() ));
					usedParams.push_back(limit);
					flagsApplied += 'l';
				} else {
					channel->setUserLimit(0);
				}
				break;

			default:
				return sendReply( data.fd, ERR_UMODEUNKNOWNFLAG );
			}
		}
	}
	std::ostringstream oss;
	oss << ":" << client.getMask() << " MODE "
		<< channel->getName() << " " << flagsApplied;
	for (size_t i = 0; i < usedParams.size(); ++i)
		oss << " " << usedParams[i];
	oss << "\r\n";
	channel->broadcast(oss.str());
}

	//NOTES :

	//if (client isn't in channel database)
		//ERR_NOTONCHANNEL
	//else if (only 1 param)
		//if (param == channel database)
			//RPL_CHANNELMODEIS
		//else if (param == client nickname)
			//RPL_UMODEIS (+ client modes)
		//else
			//ERR_NOSUCHCHANNEL
	//else if(!channel OR !flag/mods)
		//ERR_NEEDMOREPARAMS
	
	//if (flags/modes != i OR j OR t OR o OR k OR l)
		//ERR_UMODEUNKNOWNFLAG

	//if (channel not in database)
		//ERR_NOSUCHCHANNEL
	//else if (client not OP)
		//ERR_CHANOPRIVSNEEDED
	//if (flag/mods == o AND !target)
		//ERR_NEEDMOREPARAMS
		//else if (target not in channel data)
			//ERR_NOTONCHAMNNEL
		//else if ("+o")
			//promote target to OP + message saying "+o target" ON CHANNEL
		//else if ("-o")
			//demote target from OP + message saying "-o target" ON CHANNEL
	//else if (flags/mods == i)
		//message telling channel is +i or -i on channel
	//else if (flags == t)
		//message telling channel is +t or -t on channel
	//else if (flag ==  k)
		//if (flag == +k AND !pass)
			//ERR_NEEDMOREPARAMS
		//else if (flag == +k AND new pass == old pass)
			//ERR_KEYSET
		//else
			//:irc.example.net MODE #chatroom +k secret
	//else if (flag == l)
		//if (+l AND !limit)
			//ERR_NEEDMOREPARAMS
		//else if ("+l")
			//set user limit to limit : :irc.example.net MODE #chatroom +l 10
		//else
			//remove set limit 

/* MODE - Change the channel’s mode:
· i: Set/remove Invite-only channel
· t: Set/remove the restrictions of the TOPIC command to channel operators
· k: Set/remove the channel key (password)
· o: Give/take channel operator privilege
· l: Set/remove the user limit to channel */