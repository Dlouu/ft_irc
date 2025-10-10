#include "Command.hpp"

void	Command::privmsgCommand( const CommandData_t& data ) const {
	Client	*executor = Server::getClientByFD( data.fd );
	std::string	cleanMsg = data.message.substr( 7, data.message.size() - 7 );

	// find start pos of the channel name
	std::string::size_type chanNameStartPos = std::string::npos;
	for ( unsigned int i = 0; i < cleanMsg.size(); i++ ) {
		if ( cleanMsg[ i ] != ' ' && cleanMsg[ i ] != '\t' ) {
			chanNameStartPos = i;
			break ;
		}
	}
	if ( chanNameStartPos == std::string::npos )
		return ( sendReply( executor->getFD(), ERR_NORECIPIENT ) );

	std::string ::size_type chanNameEndPos = std::string::npos;
	for ( unsigned int i = chanNameStartPos; i < cleanMsg.size(); i++ ) {
		if ( cleanMsg[ i ] == ' ' || cleanMsg[ i ] == '\t' ) {
			chanNameEndPos = i;
			break ;
		}
	}

	// split channel names, if the request have a syntax error like having a space after a coma then all next targets will be ignored.
	std::string chanNames = cleanMsg.substr( chanNameStartPos, chanNameEndPos - chanNameStartPos );
	std::vector< std::string > chanList = this->split( cleanMsg.substr( chanNameStartPos, chanNameEndPos - chanNameStartPos ), ',' );

	// Find the separator between chan name and the message, if not found then there is no message and we send back an error to the user
	// also check if there is a char after the separator.
	size_t	sepPos = cleanMsg.find( ':' );
	if ( sepPos == std::string::npos || sepPos + 1 >= cleanMsg.size() )
		return ( sendReply( executor->getFD(), ERR_NOTEXTTOSEND ) );

	std::string message = cleanMsg.substr( sepPos + 1, cleanMsg.size() - sepPos - 1 );

	for ( unsigned int i = 0; i < chanList.size(); i++ ) {
		std::string name = chanList[ i ];
		// check if first char is valid
		char	tmp[] = { '#', '&', '+', '!' };
		bool	isChan = false;
		for ( unsigned int j = 0; j <= 3; j++ ) {
			if ( name[ 0 ] == tmp[ j ] ) {
				isChan = true;
				break ;
			}
		}

		// if chan, check if chan exist and if user is in chan, else check if user exist then send message
		if ( isChan ) {
			Channel	*channel = Server::getChannel( name );

			if ( !channel ) {
				return ( sendReply( executor->getFD(), ERR_NOSUCHCHANNEL ) );
			} else if ( !channel->isClientUser( *executor ) ) {
				return ( sendReply( executor->getFD(), ERR_CANNOTSENDTOCHAN ) );
			}
			channel->shareMessage( *executor, message, "PRIVMSG" );
		} else {
			Client	*client = Server::getClientByNick( name );
			if ( !client )
				return ( sendReply( executor->getFD(), ERR_NOSUCHNICK ) );
			client->shareMessage( *executor, message );
		}
	}
}
