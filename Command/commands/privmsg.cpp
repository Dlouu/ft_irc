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

	// Find the separator between chan name and the message, if not found then there is no message and we send back an error to the user
	size_t	sepPos = cleanMsg.find( ':' );
	if ( sepPos == std::string::npos )
		return ( sendReply( executor->getFD(), ERR_NOTEXTTOSEND ) );

	// check if first char is valid
	char	tmp[] = { '#', '&', '+', '!' };
	bool	isChan = false;
	for ( unsigned int i = 0; i <= 3; i++ ) {
		if ( cleanMsg[ chanNameStartPos ] == tmp[ i ] ) {
			isChan = true;
			break ;
		}
	}

	// check if there is a message
	if ( sepPos + 1 >= cleanMsg.size() )
		return ( sendReply( executor->getFD(), ERR_NOTEXTTOSEND ) );
	std::string message = cleanMsg.substr( sepPos + 1, cleanMsg.size() - sepPos - 1 );

	// if chan, check if chan exist and if user is in chan, else check if user exist then send message
	if ( isChan ) {
		std::string	channelName = cleanMsg.substr( chanNameStartPos, sepPos - chanNameStartPos - 1 );
		Channel	*channel = Server::getChannel( channelName );

		if ( !channel ) {
			return ( sendReply( executor->getFD(), ERR_NOSUCHCHANNEL ) );
		} else if ( !channel->isClientUser( *executor ) ) {
			return ( sendReply( executor->getFD(), ERR_CANNOTSENDTOCHAN ) );
		}
		channel->shareMessage( *executor, message, "PRIVMSG" );
	} else {
		std::string clientNick = cleanMsg.substr( chanNameStartPos, sepPos - chanNameStartPos - 1 );
		Client	*client = Server::getClientByNick( clientNick );
		if ( !client )
			return ( sendReply( executor->getFD(), ERR_NOSUCHNICK ) );
		client->shareMessage( *executor, message );
	}
}
