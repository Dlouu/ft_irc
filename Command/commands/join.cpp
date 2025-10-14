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
	Client	*executor = Server::getClientByFD( data.fd );
	if ( !executor )
		return ( sendReply( data.fd, ERR_NEEDMOREPARAMS ) );

	std::string cleanMsg = data.message.substr( 5, data.message.size() - 5 );

	std::vector< std::string > canalsData = this->split( cleanMsg, ' ' );
	std::vector< std::string > channels = this->split( canalsData[ 0 ], ',' );
	std::vector< std::string > passwords;

	int fd = executor->getFD();

	if ( canalsData.size() > 1 ) {
		passwords = this->split( canalsData[ 1 ], ',' );
	}

	for ( size_t i = 0; i < channels.size(); i++ ) {
		g_vars[ "channel" ] = channels[ i ];
		if ( !isChannelMaskValid( channels[ i ] ) ) {
			sendReply( fd, ERR_BADCHANMASK );
			continue ;
		} else if ( executor->getChannels().size() == Client::maxChannel )
			return ( sendReply( fd, ERR_TOOMANYCHANNELS ) );

		if ( Server::DoesChannelExist( channels[ i ] ) ) {
			Channel	*channelObj = NULL;
			channelObj = Server::getChannel( channels[ i ] );
			if ( channelObj->isClientUser( *executor ) ) {
				sendReply( fd, ERR_USERONCHANNEL );
				continue ;
			} else if ( channelObj->isClientBan( *executor ) ) {
				sendReply( fd, ERR_BANNEDFROMCHAN );
				continue ;
			} else if ( channelObj->getUserCount() >= channelObj->getUserLimit() ) {
				sendReply( fd, ERR_CHANNELISFULL );
				continue ;
			} else if ( channelObj->isInviteOnly() && !channelObj->hasAnInvitation( *executor ) ) {
				sendReply( fd, ERR_INVITEONLYCHAN );
				continue  ;
			} else if ( channelObj->isPasswordSet() && ( i >= passwords.size() || !channelObj->isPasswordCorrect( passwords[ i ] ) ) ) {
				sendReply( fd, ERR_BADCHANNELKEY );
				continue;
			}
			channelObj->addUser( *executor );
			channelObj->Welcome( *executor );
			LOGC( DEBUG ) << "User '" << executor->getMask() << "' joined the channel " << channelObj->getName();
		} else {
			Channel	channelObj = Channel( channels[ i ] );
			channelObj.addUser( *executor );
			channelObj.addOperator( *executor );
			Server::addChannel( channelObj );
			channelObj.Welcome( *executor );
			LOGC( DEBUG ) << "User '" << executor->getMask() << "' created the channel " << channelObj.getName();
		}
	}
}
