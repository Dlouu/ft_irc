#include "Command.hpp"

void	Command::topicCommand( const CommandData_t& data ) const {
	std::cout << "TOPIC command called" << std::endl;
	(void)data;
}
