#include "./../../Command/Command.hpp"

static int	invalidChar( const char *nickname ) {
	for (int i = 0; nickname[i]; i++) {
		if (nickname[i] == ','
			|| nickname[i] == '*'
			|| nickname[i] == '?'
			|| nickname[i] == '!'
			|| nickname[i] == '@'
			|| nickname[i] == '.'
			|| nickname[i] == ':'
			|| nickname[i] == '#'
			|| nickname[i] == '&')
			return (1);
		if (!isascii(nickname[i]))
			return (1);
	}
	return (0);
}

static int	invalidNickname( const std::string& nickname ) {
	if (nickname.find(" ") != std::string::npos)
		return (1);
	else if (invalidChar( nickname.c_str() ))
		return (1);
	else if (nickname.length() > 30)
		return (1);
	return (0);
}

static int	alreadyRegistered( const std::string& nickname, int fd ) {
	(void)fd;
	std::map<int, Client> clients = Server::getClients();
	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++) {
		if (it->second.getNickname() == nickname) {
			return (1);
		}
	}
	return (0);
}

void	Command::nickCommand( const CommandData_t& data ) const {
	std::string nickname = data.message.substr( 5, data.message.length() );
	std::string	oldnick = Server::getClientByFD(data.fd).getNickname();

	if (nickname.empty()) {
		return sendReply( data.fd, ERR_NONICKNAMEGIVEN );
	} else if (invalidNickname( nickname )) {
		return sendReply( data.fd, ERR_ERRONEUSNICKNAME );
	} else {
		while (alreadyRegistered( nickname, data.fd )) {
			Server::setNicknameByFD( data.fd, "* " + nickname );
			return (sendReply( data.fd, ERR_NICKNAMEINUSE ));
			//ou le remettre que dans already registred
		}
		Server::setNicknameByFD( data.fd, nickname );
		Server::setNickSetByFD( data.fd, true );
	}
	if (Server::isClientRegistered( data.fd )) {
		if (Server::isClientWelcomed( data.fd ) == false) {
			sendReply( data.fd, RPL_WELCOME );
			sendReply( data.fd, RPL_YOURHOST );
			sendReply( data.fd, RPL_CREATED );
			sendReply( data.fd, RPL_MYINFO );

			// Send MOTD
			sendReply( data.fd, RPL_MOTDSTART );
			sendReply( data.fd, RPL_MOTD );
			sendReply( data.fd, RPL_ENDOFMOTD );
			Server::setWelcomeStatusByFD( data.fd, true );
		} else {
			std::string	reply = ":" + oldnick
				+ "!" + Server::getClientByFD( data.fd ).getUsername()
				+ "@" + Server::getClientByFD( data.fd ).getHostname()
				+ " NICK " + Server::getClientByFD( data.fd ).getNickname() + "\r\n";
			send( data.fd, reply.c_str(), reply.size(), 0 );
			std::cout << GRE "<<< " END << reply;
		}
	}
}

	//NOTES:
	//if (nickname param empty)
		//ERR_NONICKNAMEGIVEN
	//else if (nickname param already in database)
		//ERR_NICKNAMEINUSE
	//else if (invalid nickname)
			// nickname is considered invalid if:
			// It contains spaces.
			// It contains disallowed special characters (varies per server, but often excludes , * ? ! @ . : # & at certain positions).
			// It starts with a character not allowed (most servers require it to start with a letter or special symbol like _ or [ but not a number).
			// It exceeds the maximum length (commonly 9 or 30 characters, depending on server config).
			// It violates server-specific nickname rules. 
		//ERR_ERRONEUSNICKNAME
	//else
		//if (client was not already registered) 
			//register nickname in database
			//client nick set == true
		//else (server 000 :<oldnick>!<user>@<host> NICK :<newnick>)
