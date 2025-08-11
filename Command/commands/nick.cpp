#include "./../../Command/Command.hpp"

void	Command::nickCommand( const CommandData_t& data ) const {
	Server *server = Server::GetInstance();
	std::string nickname;
	nickname = data.message.substr( 5, data.message.length() );

	// if ( nickname.() )
 	// 	return ; // ERR_ERRONEUSNICKNAME
	if ( nickname.empty() )
		return ; // ERR_NONICKNAMEGIVEN
	if ( server->_users[ data.fd ].getNickname() == nickname )
		return ; // ERR_NICKNAMEINUSE

	server->_users[ data.fd ].setNickname( nickname );
}
