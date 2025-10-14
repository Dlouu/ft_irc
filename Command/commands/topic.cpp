#include "Command.hpp"

void	Command::topicCommand( const CommandData_t& data ) const {
	Client		*client		= Server::getClientByFD( data.fd );
	Channel		*channel	= NULL;
	std::string	topic		= "";
	size_t		topicPos	= 0;

	if ( !client )
		return ;

	if ((topicPos = data.message.find(":") + 1) == std::string::npos)
		return sendReply( data.fd, ERR_NEEDMOREPARAMS );
	topic = data.message.substr( topicPos, data.message.length() - topicPos );

	std::vector<std::string> params = split( data.message, ' ' );
	g_vars[ "command" ] = params[0];

	//check params and channel
	if (params.size() < 2) {
		return sendReply( data.fd, ERR_NEEDMOREPARAMS );
	}
	else if (params.size() >= 2) {
		g_vars[ "channel" ] = params[1];
		if (Server::DoesChannelExist( params[1] ) == false) {
			return sendReply( data.fd, ERR_NOSUCHCHANNEL );
		}
		channel = Server::getChannel( params[1] );
	}

	//manage topic
	if (params.size() == 2) {
		if (channel->getTopic().empty()) {
			sendReply( data.fd, RPL_NOTOPIC );
		}
		sendReply( data.fd, RPL_TOPIC );
	} else if (channel->isTopicRestricted() && !channel->isClientOperator( *client )) {
		sendReply( data.fd, ERR_CHANOPRIVSNEEDED );
	} else if (!channel->isClientUser( *client )) {
		sendReply( data.fd, ERR_NOTONCHANNEL );
	} else {
		channel->setTopic( topic.substr(0, topic.size()) );
		g_vars[ "topic" ] = channel->getTopic();
		channel->shareMessage( *client, channel->getTopic(), "TOPIC" );
		sendReply( data.fd, RPL_TOPIC );
	}
}
