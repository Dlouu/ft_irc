#include "./../../Command/Command.hpp"

void	Command::nickCommand( const CommandData_t& data ) const {
	std::string nickname = data.message.substr( 5, data.message.length() );

	std::map<int, Client> clients = Server::getClients();
	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++) {
		std::cout << it->second.getNickname()  << std::endl;
		if (it->second.getNickname() == nickname) {
			return sendReply( data.fd, ERR_NICKNAMEINUSE );
		}
	}
	if (nickname.empty())
		return sendReply( data.fd, ERR_NONICKNAMEGIVEN );
	//else if (invalid nickname)
			// nickname is considered invalid if:
			// It contains spaces.
			// It contains disallowed special characters (varies per server, but often excludes , * ? ! @ . : # & at certain positions).
			// It starts with a character not allowed (most servers require it to start with a letter or special symbol like _ or [ but not a number).
			// It exceeds the maximum length (commonly 9 or 30 characters, depending on server config).
			// It violates server-specific nickname rules.
		//return sendReply( data.fd, ERR_ERRONEUSNICKNAME );
	//else
		//if (client was not already registered)
			//register nickname in database
			//client nick set == true
		//else (server 000 :<oldnick>!<user>@<host> NICK :<newnick>)

	Server::setNicknameByFD( data.fd, nickname );
	Server::getClientByFD( data.fd )->setFD( data.fd );
}
