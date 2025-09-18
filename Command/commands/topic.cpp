#include "Command.hpp"

void	Command::topicCommand( const CommandData_t& data ) const {
	Server		*server		= Server::getInstance();
	Client		&client		= *server->getClientByFD( data.fd );
	Channel		*channel	= NULL;

	std::vector<std::string> params = split( data.message, ' ' );
	g_vars[ "command" ] = params[0];

	//check params and channel
	if (params.size() < 2) {
		return sendReply( data.fd, ERR_NEEDMOREPARAMS );
	}
	else if (params.size() >= 2) {
		g_vars[ "channel" ] = params[1];
		if (server->isChannelExist( params[1] ) == false) {
			return sendReply( data.fd, ERR_NOSUCHCHANNEL );
		}
		channel = server->getChannel( params[1] );
	}

	//manage topic
	if (params.size() == 2) {
		if (channel->getTopic().empty()) {
			sendReply( data.fd, RPL_NOTOPIC );
		}
		sendReply( data.fd, RPL_TOPIC );
	} else if (channel->isTopicRestricted() && !channel->isClientOperator( client )) {
		sendReply( data.fd, ERR_CHANOPRIVSNEEDED );
	} else if (!channel->isClientUser( client )) {
		sendReply( data.fd, ERR_NOTONCHANNEL );
	} else {
		channel->setTopic( client, params[2].substr(1, params[2].size()) );
		g_vars[ "topic" ] = channel->getTopic();
		channel->shareMessage( client, channel->getTopic(), "TOPIC" );
		sendReply( data.fd, RPL_TOPIC );
	}
}

	//if (<channel> is empty)
		//ERR_NEEDMOREPARAMS
	//if (<channel> doesn't exist)
		//ERR_NOSUCHCHANNEL
	//else if (<topic> empty AND topic data is empty)
		//RPL_NOTOPIC
	//else if (channel mode +t AND client not OP)
		//ERR_CHANOPRIVSNEEDED
	//else if (client not in channel)
		//ERR_NOTONCHANNEL
	//else
		//change topic message in database
		//RPL_TOPIC

	//	If the <topic> parameter is an empty string, the
	//	topic for that channel will be removed
