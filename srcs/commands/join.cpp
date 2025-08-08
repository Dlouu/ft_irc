#include "Command.hpp"

void	Command::joinCommand( const CommandData_t& data ) const {
	std::cout << "JOIN command called" << std::endl;
	(void)data;
}
