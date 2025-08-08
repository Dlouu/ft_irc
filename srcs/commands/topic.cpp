#include "Command.hpp"
#include "Colors.hpp"

void	Command::topicCommand( const CommandData_t& data ) const {
	std::cout << MAG "TOPIC command called" END << std::endl;
	(void)data;
}
