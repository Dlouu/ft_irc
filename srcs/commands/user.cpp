#include "Command.hpp"

void	Command::userCommand( const CommandData_t& data ) const {
	std::string user;
	std::cout << "USER command called" << std::endl;
	(void)data.fd; //a use pour la map

	user = data.message.substr(5, data.message.length());
	std::cout << "USER=" << user << std::endl;
}
