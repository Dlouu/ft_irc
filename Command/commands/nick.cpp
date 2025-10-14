#include "Command.hpp"

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

static int	alreadyRegistered( const std::string& nickname ) {
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
	Client	*client = Server::getClientByFD(data.fd);

	if (!client)
		return;

	std::string	oldnick = client->getNickname();

	if (!Server::isClientPass(data.fd))
		return;
	if (nickname.empty()) {
		return sendReply( data.fd, ERR_NONICKNAMEGIVEN );
	} else if (invalidNickname( nickname )) {
		return sendReply( data.fd, ERR_ERRONEUSNICKNAME );
	} else {
		while (alreadyRegistered( nickname )) {
			client->setNickname( "* " + nickname );
			return (sendReply( data.fd, ERR_NICKNAMEINUSE ));
		}
		client->setNickname( nickname );
		client->setFD( data.fd );
		client->setNickSet( true );
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
			client->setWelcomeStatus( true );
		} else {
			std::string	reply = ":" + oldnick
				+ "!" + client->getUsername()
				+ "@" + client->getHostname()
				+ " NICK " + client->getNickname();
			LOGC( SERVER ) << reply;
			reply += "\r\n";
			send( data.fd, reply.c_str(), reply.size(), MSG_DONTWAIT );
		}
	}
}
