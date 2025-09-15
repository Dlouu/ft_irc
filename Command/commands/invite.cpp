#include "Command.hpp"

void	Command::inviteCommand( const CommandData_t& data ) const {
	Server		*server		= Server::getInstance();
	Client		&client		= *server->getClientByFD( data.fd );
	Client		*invitee	= NULL;
	Channel		*channel	= NULL;

	std::vector<std::string> params = split( data.message, ' ' );
	g_vars[ "command" ] = params[0];

	//check params and channel
	if (params.size() < 3) {
		return sendReply( data.fd, ERR_NEEDMOREPARAMS );
	}
	else if (params.size() >= 3) {
		g_vars[ "target" ] = params[1];
		g_vars[ "channel" ] = params[2];
		if (server->isChannelExist( params[2] ) == false) {
			return sendReply( data.fd, ERR_NOSUCHCHANNEL );
		}
		channel = server->getChannel( params[2] );
		if (server->getClientByNick( params[1] ) == NULL) {
			return sendReply( data.fd, ERR_NOSUCHNICK );
		}
		invitee = server->getClientByNick( params[1] );
	}

	//manage invite
	if (!channel->isClientOperator( client )) {
		return sendReply( data.fd, ERR_CHANOPRIVSNEEDED );
	} else if (!channel->isClientUser( client )) {
		return sendReply( data.fd, ERR_NOTONCHANNEL );
	} else if (channel->isClientUser( *invitee ) || channel->isClientOperator( *invitee )) {
		sendReply( data.fd, ERR_USERONCHANNEL );
	} else {
		//faut-il faire une liste d'invitees
		channel->shareMessage( client, *invitee, channel->getName(), "INVITE" );
		sendReply( data.fd, RPL_INVITING );
	}

	//if (!invitee || !channel)
		//ERR_NEEDMOREPARAMS
	//if (client not on channel)
		//ERR_NOTONCHANNEL
	//else if (client not OP in channel in mode +i)
		//ERR_CHANOPRIVSNEEDED
	//else if (invitee not in databse)
		//ERR_NOSUCHNICK
	//else if (invitee already in channel)
		//ERR_USERONCHANNEL
	//else 
		//send(RPL_INVITING)
}
