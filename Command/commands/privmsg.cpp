#include "./../../Command/Command.hpp"

void	Command::privmsgCommand( const CommandData_t& data ) const {
	std::cout << MAG "PRIVMSG command called" END << std::endl;

	Client	*executor = Server::getClientByFD( data.fd );
	std::string	cleanMsg = data.message.substr( 8, data.message.size() - 8 );
	size_t	sepPos = cleanMsg.find( ':' );
	std::string	channelName = cleanMsg.substr( 0, sepPos - 1 );
	std::string	message = cleanMsg.substr( sepPos + 1, cleanMsg.size() - channelName.size() );
	LOGC( INFO ) << "Channel name: " << channelName;
	LOGC( INFO ) << "Message: " << message;

	Channel	*channel = Server::getChannel( channelName );
	if ( !channel )
		return ;
	channel->shareMessage( *executor, message );
}
