#include "./../../Command/Command.hpp"

void	Command::capCommand( const CommandData_t& data ) const {
	std::string response;

	std::cout << MAG "CAP command called" END << std::endl;
	if ( data.message == "CAP LS" ) {
		response = "CAP * LS :\r\n";
		if ( send( data.fd, response.c_str(), response.length(), 0 ) == -1 ) {
			std::cerr << RED "Error sending response" END << std::endl;
		}
	} else if ( data.message == "CAP END" ) {
		std::string username = Server::GetClientByFD( data.fd ).getNickname();
		response = ":localhost 001 " + username + " :Welcome to the Internet Relay Network " + username + "\r\n";

		if ( send( data.fd, response.c_str(), response.length(), 0 ) == -1 ) {
			std::cerr << RED "Error sending response" END << std::endl;
		}
	}
	std::cout << GRE "<<< " END << response;
}

