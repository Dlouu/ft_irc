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
		g_vars = fillVars( data.fd );
		std::string nickname = Server::GetClientByFD(data.fd).getNickname();
		std::cout << nickname << "GRRTRTHRHT" << std::endl;
		response = formatReply( RPL_WELCOME, g_vars );
	if ( send( data.fd, response.c_str(), response.length(), 0 ) == -1 ) {
		std::cerr << RED "Error sending response" END << std::endl;
		}
	}
	std::cout << GRE "<<< " END << response;
}

// mettre les reponses dans un buffer du client et faire une fonction qui send et est protegee (Dlou)