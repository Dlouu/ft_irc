#include "Command.hpp"

bool	isChannelMaskValid( std::string name ) {
	if ( name.length() <= 1 || name.length() > 200 )
		return ( false );
	else if ( name[ 0 ] != '#' && name[ 0 ] != '&' )
		return ( false );

	char	tmp[] = { ',', '?', '*', '\a' };
	std::vector< char >	unallowedChar( tmp, tmp + sizeof( tmp ) / sizeof( tmp[ 0 ] ) );
	for ( unsigned int i = 0; i < unallowedChar.size(); i++ ) {
		size_t pos = name.find( unallowedChar[ i ] );
		if ( pos != name.npos )
			return ( false );
	}
	return ( true );
}

void	Command::joinCommand( const CommandData_t& data ) const {

	Server	*server = Server::getInstance();
	Client	*executor = server->getClientByFD( data.fd );
	if ( !executor )
		return ( sendReply( data.fd, ERR_NEEDMOREPARAMS ) );

	std::string cleanMsg = data.message.substr( 5, data.message.size() - 5 );
	LOGC( INFO ) << data.message;
	LOGC( INFO ) << cleanMsg;

	std::vector< std::string > canalsData = this->split( cleanMsg, ' ' );
	std::vector< std::string > channels = this->split( canalsData[ 0 ], ',' );
	std::vector< std::string > passwords;

	if ( canalsData.size() > 1 ) {
		passwords = this->split( canalsData[ 1 ], ',' );
	}

	for ( size_t i = 0; i < channels.size(); i++ ) {
		g_vars[ "channel" ] = channels[ i ];
		if ( !isChannelMaskValid( channels[ i ] ) ) {
			sendReply( executor->getFD(), ERR_BADCHANMASK );
			continue ;
		} else if ( executor->getChannels().size() == Client::maxChannel )
			return ( sendReply( executor->getFD(), ERR_TOOMANYCHANNELS ) );

		if ( server->isChannelExist( channels[ i ] ) ) {
			Channel	*channelObj = NULL;
			LOGC( INFO ) << "Channel exist";
			channelObj = server->getChannel( channels[ i ] );
			if ( channelObj->isClientUser( *executor ) ) {
				sendReply( executor->getFD(), ERR_USERONCHANNEL );
				continue ;
			} else if ( channelObj->isClientBan( *executor ) ) {
				sendReply( executor->getFD(), ERR_BANNEDFROMCHAN );
				continue ;
			} else if ( channelObj->getUserCount() >= channelObj->getUserLimit() ) {
				sendReply( executor->getFD(), ERR_CHANNELISFULL );
				continue ;
			} else if ( channelObj->isInviteOnly() && !channelObj->hasAnInvitation( *executor ) ) {
				sendReply( executor->getFD(), ERR_INVITEONLYCHAN );
				continue  ;
			} else if ( channelObj->isPasswordSet() && ( i >= passwords.size() || !channelObj->isPasswordCorrect( passwords[ i ] ) ) ) {
				sendReply( executor->getFD(), ERR_BADCHANNELKEY );
				continue;
			}
			channelObj->addUser( *executor );
		} else {
			LOGC( INFO ) << "Channel doesn't exist";
			Channel	channelObj = Channel( channels[ i ] );
			channelObj.addUser( *executor );
			channelObj.addOperator( *executor );
			server->addChannel( channelObj );
		}
	}
	//if (no client or no channel param)
		//ERR_NEEDMOREPARAMS
	//else if (channel mode is +i (invite only))
		//ERR_INVITEONLYCHAN
	//else if (channel doesn't exit)
		//ERR_NOSUCHCHANNEL
	//else if (channel name isn't in good format (e.g. no '#' before channel name)) A valid channel name typically:
		//ERR_BADCHANMASK	// Begins with # or &
							// Has 1–200 characters
							// Cannot contain spaces, ASCII BEL (0x07), comma ,, or the channel type prefixes # / & / + / ! inside
							// Wildcards (*, ?) are generally not allowed unless specifically implemented for masks
							//source : chat gpt t'inquiete
	//else if (channel is full)
		//ERR_CHANNELISFULL
	//else if (client is in ban list of the channel)
		//ERR_BANNEDFROMCHAN
	//else if (password is wrong)
		//ERR_BADCHANNELKEY
	//else if (client joined too many channels (>10?))
		//ERR_TOOMANYCHANNELS
	//else
		//RPL_TOPIC and RPL_NAMREPLY
}
