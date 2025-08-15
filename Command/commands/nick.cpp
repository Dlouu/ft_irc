#include "./../../Command/Command.hpp"

void	Command::nickCommand( const CommandData_t& data ) const {
	std::string nickname;
	nickname = data.message.substr( 5, data.message.length() );
	// if ( nickname.() )
 	// 	return ; // ERR_ERRONEUSNICKNAME
	if ( nickname.empty() )
		return ; // ERR_NONICKNAMEGIVEN
	std::string	error = "";

	std::map< int, Client > clients = Server::getClients();

	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++) {
		std::cout << it->second.getNickname()  << std::endl;
		if (it->second.getNickname() == nickname) {
			g_vars = fillVars( data.fd );
			std::string response = formatReply( ERR_NICKNAMEINUSE, g_vars );
			if ( send( data.fd, response.c_str(), response.length(), 0 ) == -1 ) {
				std::cerr << RED "Error sending response" END << std::endl;
			}
			std::cout << GRE "<<< " END << response;
			return ;
		}
	}
	Server::setNicknameByFD( data.fd, nickname );
}
