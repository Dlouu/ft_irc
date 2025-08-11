#include "./../../Command/Command.hpp"

void	Command::nickCommand( const CommandData_t& data ) const {
	std::string nickname;
	std::cout << MAG "NICK command called" END << std::endl;
	( void )data.fd;

	nickname = data.message.substr( 5, data.message.length() );
	std::cout << BLU "NICK=" END << nickname << std::endl;
}
