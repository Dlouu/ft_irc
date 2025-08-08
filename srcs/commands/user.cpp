#include "Command.hpp"
#include "Colors.hpp"

void	Command::userCommand( const CommandData_t& data ) const {
	std::string user;
	std::cout << MAG << "USER command called" END << std::endl;
	(void)data.fd;

	user = data.message.substr(5, data.message.length());
	std::cout << BLU "USER=" END << user << std::endl;
}
