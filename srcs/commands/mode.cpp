#include "Command.hpp"

void	Command::modeCommand( const CommandData_t& data ) const {
	std::cout << "MODE command called" << std::endl;
	(void)data;
}
