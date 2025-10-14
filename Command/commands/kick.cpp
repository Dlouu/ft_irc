#include "Command.hpp"

void	Command::kickCommand( const CommandData_t& data ) const {
	Client		&client		= *Server::getClientByFD( data.fd );
	Channel		*channel	= NULL;

	std::vector<std::string> params = split( data.message, ' ' );
	g_vars[ "command" ] = params[0];

	//check params and channel
	if (params.size() < 3) {
		return sendReply( data.fd, ERR_NEEDMOREPARAMS );
	}
	else if (params.size() >= 3) {
		g_vars[ "channel" ] = params[1];
		if (params[1][0] != '#' && params[1][0] != '&') {
			return sendReply( data.fd, ERR_BADCHANMASK );
		}
		g_vars[ "target" ] = params[2];
		if (params.size() > 3) {
			g_vars[ "reason" ] = params[3].substr(1, params[3].size());
		} else {
			g_vars[ "reason" ] = "";
		}
		if (Server::DoesChannelExist( params[1] ) == false) {
			return sendReply( data.fd, ERR_NOSUCHCHANNEL );
		}
		channel = Server::getChannel( params[1] );
		if (Server::getClientByNick( params[2] ) == NULL) {
			return sendReply( data.fd, ERR_NOSUCHNICK );
		}
	}
	Client	*target = Server::getClientByNick( params[2] );

	//manage kick
	if (!channel->isClientOperator( client )) {
		return sendReply( data.fd, ERR_CHANOPRIVSNEEDED );
	} else if (!channel->isClientUser( client )) {
		return sendReply( data.fd, ERR_NOTONCHANNEL );
	} else if (!channel->isClientUser( *target )) {
		return sendReply( data.fd, ERR_USERNOTINCHANNEL );
	} else {
		sendMessage( target->getFD(), ":" + client.getMask() + " KICK {channel} {target} :{reason}" );
		channel->shareMessage( client, target->getNickname(), "KICK", g_vars["reason"]);
		channel->delUser( *target );
	}
}
