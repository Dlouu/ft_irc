#include "./../../Command/Command.hpp"

void	Command::nickCommand( const CommandData_t& data ) const {
	std::string nickname;
	nickname = data.message.substr( 5, data.message.length() );
	// if ( nickname.() )
 	// 	return ; // ERR_ERRONEUSNICKNAME
	if ( nickname.empty() )
		return sendReply( data.fd, ERR_NONICKNAMEGIVEN );
	std::string	error = "";

	std::map< int, Client > clients = Server::getClients();

	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++) {
		std::cout << it->second.getNickname()  << std::endl;
		if (it->second.getNickname() == nickname) {
			return sendReply( data.fd, ERR_NICKNAMEINUSE );
		}
	}
	Server::setNicknameByFD( data.fd, nickname );
}
