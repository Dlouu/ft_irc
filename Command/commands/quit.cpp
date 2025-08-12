#include "./../../Command/Command.hpp"

void	Command::quitCommand( const CommandData_t& data ) const {
	std::cout << MAG "QUIT command called" END << std::endl;
	( void )data;
}
