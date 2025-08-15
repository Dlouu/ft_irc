#include "./../../Command/Command.hpp"

void	Command::userCommand( const CommandData_t& data ) const {
	std::string user;
	std::cout << MAG << "USER command called" END << std::endl;

	user = data.message.substr( 5, data.message.length() );
	std::cout << BLU "USER=" END << user << std::endl;
	sendReply( data.fd, RPL_WELCOME );
}
