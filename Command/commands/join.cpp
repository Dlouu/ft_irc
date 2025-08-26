#include "./../../Command/Command.hpp"

void	Command::joinCommand( const CommandData_t& data ) const {
	std::cout << MAG "JOIN command called" END << std::endl;

	Server	*server = Server::getInstance();
	Client	*executor = server->getClientByFD( data.fd );
	if ( !executor )
		return ;

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
		if ( server->isChannelExist( channels[ i ] ) ) {
			Channel	*channelObj = NULL;
			LOGC( INFO ) << "Channel exist";
			channelObj = server->getChannel( channels[ i ] );
			if ( i < passwords.size() && !channelObj->isPasswordCorrect( passwords[ i ] ) )
				continue;
			channelObj->addUser( *server, *executor );
		} else {
			LOGC( INFO ) << "Channel doesn't exist";
			Channel	channelObj = Channel( channels[ i ], i < passwords.size() ? passwords[ i ] : "x" );
			channelObj.addUser( *server, *executor );
			channelObj.addOperator( *server, *executor );
			server->addChannel( channelObj );
		}
	}
}
