#include "Command.hpp"
#include "Colors.hpp"

void	Command::modeCommand( const CommandData_t& data ) const {
	std::cout << MAG "MODE command called" END << std::endl;
	(void)data;
}
