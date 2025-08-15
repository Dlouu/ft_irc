#include "./../../Command/Command.hpp"

void	Command::capCommand( const CommandData_t& data ) const {
	// std::string response;
	( void )data;
	std::cout << MAG "CAP command called" END << std::endl;
	// if ( data.message == "CAP LS" ) {
	// 	response = "CAP * LS :\r\n";
	// 	if ( send( data.fd, response.c_str(), response.length(), 0 ) == -1 ) {
	// 		std::cout << data.fd << " GROS CACA 2\n";
	// 		std::cerr << RED "Error sending response" END << std::endl;
	// 	}
	// } else if ( data.message == "CAP END" ) {
	// 	g_vars = fillVars( data.fd );
	// 	std::cout << data.fd << " GROS CACA 3\n";
	// 	std::string nickname = Server::getClientByFD(data.fd).getNickname();
	// 	std::cout << nickname << "Nickname dans Dans CAP avec getClientByFD" << std::endl;
	// 	response = formatReply( RPL_WELCOME, g_vars );
	// if ( send( data.fd, response.c_str(), response.length(), 0 ) == -1 ) {
	// 	std::cout << data.fd << " GROS CACA 4\n";
	// 	std::cerr << RED "Error sending response" END << std::endl;
	// 	}
	// }
	// std::cout << GRE "<<< " END << response;
}

// mettre les reponses dans un buffer du client et faire une fonction qui send et est protegee (Dlou)