#include "Command.hpp"
#include "Colors.hpp"

void	Command::joinCommand( const CommandData_t& data ) const {
	std::cout << MAG "JOIN command called" END << std::endl;
	(void)data;
}
