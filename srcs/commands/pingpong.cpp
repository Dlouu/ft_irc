#include "Command.hpp"

void	Command::pingCommand( const CommandData_t& data ) const {
	std::cout << "PING command called" << std::endl;
	(void)data;
}

void	Command::pongCommand( const CommandData_t& data ) const {
	std::cout << "PONG command called" << std::endl;
	(void)data;
}
