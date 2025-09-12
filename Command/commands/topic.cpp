#include "Command.hpp"

/*
Verifier si mon setTopic marche bien, voir si j'ai choke sur les n* des params
Pour le moment c'est pas ouf Huhu
*/

void	Command::topicCommand( const CommandData_t& data ) const {
	Client	&client = *Server::getClientByFD( data.fd );
	Channel	*channel;

	std::vector<std::string> params = split( data.message, ' ' );

	if (params.size() >= 2) {
		channel = Server::getInstance()->getChannel( params[3] );
		if (!channel) {
			sendReply( data.fd, ERR_NOSUCHCHANNEL );
		}
	}
	if (params.size() == 2) {
		sendReply( data.fd, RPL_TOPIC );
	}
	else if (params.size() >= 3 && params[2].empty() && channel->getTopic() == "") {
		sendReply( data.fd, RPL_NOTOPIC ); // a verifier, la description est bizarre
	} else if (channel->isTopicRestricted() && channel->isClientOperator( client )) {
		sendReply( data.fd, ERR_CHANOPRIVSNEEDED );
	} else if (channel->isClientUser( client )) {
		sendReply( data.fd, ERR_NOTONCHANNEL );
	} else {
		channel->setTopic( client, params[2] );
		LOGC( INFO ) << channel->getTopic();
		g_vars[ "topic" ] = channel->getTopic();
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
