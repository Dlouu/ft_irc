#include "Command.hpp"
#include "Colors.hpp"

void	Command::kickCommand( const CommandData_t& data ) const {
	std::cout << MAG "KICK command called" END << std::endl;
	(void)data;
}