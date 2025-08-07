#include "Command.hpp"

void	Command::inviteCommand( const CommandData_t& data ) const {
	std::cout << "INVITE command called" << std::endl;
	(void)data;
}
