#include "Command.hpp"
#include "Colors.hpp"

void	Command::pingCommand( const CommandData_t& data ) const {
	std::cout << MAG "PING command called" END << std::endl;
	(void)data;
}

void	Command::pongCommand( const CommandData_t& data ) const {
	std::cout << MAG "PONG command called" END << std::endl;
	(void)data;
}
