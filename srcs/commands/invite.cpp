#include "Command.hpp"
#include "Colors.hpp"

void	Command::inviteCommand( const CommandData_t& data ) const {
	std::cout << MAG "INVITE command called" END << std::endl;
	(void)data;
}
