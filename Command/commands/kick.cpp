#include "./../../Command/Command.hpp"

void	Command::kickCommand( const CommandData_t& data ) const {
	std::cout << MAG "KICK command called" END << std::endl;
	( void )data;
}