#include "Command.hpp"
#include "Colors.hpp"

void	Command::privmsgCommand( const CommandData_t& data ) const {
	std::cout << MAG "PRIVMSG command called" END << std::endl;
	(void)data;
}
