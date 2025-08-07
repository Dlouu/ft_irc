#include "Command.hpp"

void	Command::privmsgCommand( const CommandData_t& data ) const {
	std::cout << "PRIVMSG command called" << std::endl;
	(void)data;
}
