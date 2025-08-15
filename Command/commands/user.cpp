#include "./../../Command/Command.hpp"

void	Command::userCommand( const CommandData_t& data ) const {
	std::string user;
	std::cout << MAG << "USER command called" END << std::endl;

	user = data.message.substr( 5, data.message.length() );
	std::cout << BLU "USER=" END << user << std::endl;

	g_vars = fillVars( data.fd );
	std::string response = formatReply( RPL_WELCOME, g_vars );
	if ( send( data.fd, response.c_str(), response.length(), 0 ) == -1 ) {
		std::cerr << RED "Error sending response" END << std::endl;
	}
	std::cout << GRE "<<< " END << response;
}
