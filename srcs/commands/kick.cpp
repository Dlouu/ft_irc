#include "Command.hpp"

void	Command::kickCommand( const CommandData_t& data ) const {
	std::cout << "KICK command called" << std::endl;
	(void)data;
}