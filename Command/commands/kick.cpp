#include "Command.hpp"

void	Command::kickCommand( const CommandData_t& data ) const {
	Server		*server		= Server::getInstance();
	Client		&client		= *server->getClientByFD( data.fd );
	Client		*target		= NULL;
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
		if (server->isChannelExist( params[1] ) == false) {
			return sendReply( data.fd, ERR_NOSUCHCHANNEL );
		}
		channel = server->getChannel( params[1] );
		if (server->getClientByNick( params[2] ) == NULL) {
			return sendReply( data.fd, ERR_NOSUCHNICK );
		}
		target = server->getClientByNick( params[2] );
	}

	//manage kick
	if (!channel->isClientOperator( client )) {
		return sendReply( data.fd, ERR_CHANOPRIVSNEEDED );
	} else if (!channel->isClientUser( client )) {
		return sendReply( data.fd, ERR_NOTONCHANNEL );
		// AJOUTER UN CHECK TARGET ON CHAN
	} else {
		//kick from server
		LOGC( INFO ) << "SUPPRIMER L'UTILISATEUR DE LA LISTE DES FD DU CHANNEL";
		sendMessage( target->getFD(), ":" + client.getMask() + " KICK {channel} {target} :{reason}" );
		channel->shareMessage( client, target->getNickname(), "KICK", g_vars["reason"]);
	}
}

//if (no target or no channel)
	//ERR_NEEDMOREPARAMS
//else if (channel name isn't in good format (e.g. no '#' before channel name)) A valid channel name typically:
	//ERR_BADCHANMASK														// Begins with # or &
																			// Has 1–200 characters
																			// Cannot contain spaces, ASCII BEL (0x07), comma ,, or the channel type prefixes # / & / + / ! inside
																			// Wildcards (*, ?) are generally not allowed unless specifically implemented for masks 
																			//source : chat gpt t'inquiete
//else if (client not on channel)
	//ERR_NOTONCHANNEL
//else if (channel not in data)
	//ERR_NOSUCHCHANNEL
//else if (client is OP on channel)
	//ERR_CHANOPRIVSNEEDED
//else 
	//kick target from server data
	//send(<kicker>!<user>@<host> KICK <channel> <target> :<reason>)