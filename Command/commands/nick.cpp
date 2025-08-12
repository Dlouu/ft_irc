#include "./../../Command/Command.hpp"

void	Command::nickCommand( const CommandData_t& data ) const {
	Server *server = Server::GetInstance();
	std::string nickname;
	nickname = data.message.substr( 5, data.message.length() );

	// if ( nickname.() )
 	// 	return ; // ERR_ERRONEUSNICKNAME
	if ( nickname.empty() )
		return ; // ERR_NONICKNAMEGIVEN
	std::string	error = "";

	for (std::map<int, Client>::iterator it = server->_users.begin(); it != server->_users.end(); it++) {
		std::cout << it->second.getNickname()  << std::endl;
		if (it->second.getNickname() == nickname) {

			if ( send( data.fd, "<nickname> :Nickname is already in use.", 40, 0 ) == -1 ) {
				std::cerr << RED "Error sending response" END << std::endl;
			} // ERR_NICKNAMEINUSE
			return ;
		}
	}
	Server::GetClientByFD( data.fd ).setNickname( nickname );
	// server->_users[ data.fd ].setNickname( nickname );
}

// void Command::format400( const CommandData_t& data )
// {
// 	std::string reply = "";

// 	reply += "ircserver 400: blabla " + Server::GetInstance()->_users[data.fd].getNickname() + "\n\r";

// 	----send( data.fd, reply.c_str(), reply.length(), 0 );
// 	----faire une fonction qui check si client dispo, send et delete buffer
		//erase ou ""
// }
