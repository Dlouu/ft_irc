#include "./../../Command/Command.hpp"

void	Command::joinCommand( const CommandData_t& data ) const {
	std::cout << MAG "JOIN command called" END << std::endl;

	std::string cleanMsg = data.message.substr( 5, data.message.size() - 5 );
	LOGC( INFO ) << cleanMsg;

	std::vector< std::string > canals = this->split( cleanMsg, ' ' );

	for ( unsigned long i = 0; i < canals.size(); i++ ) {
		LOGC( INFO ) << canals[ i ];
	}
}
