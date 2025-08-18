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
	std::map<int, Client> clients = Server::getClients();
	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++) {
		std::cout << it->second.getNickname()  << std::endl;
		if (it->second.getNickname() == nickname) {
			sendReply( fd, ERR_NICKNAMEINUSE );
			return (1);
		}
	}
	return (0);
}

void	Command::nickCommand( const CommandData_t& data ) const {
	std::string nickname = data.message.substr( 5, data.message.length() );

	if (nickname.empty()) {
		return sendReply( data.fd, ERR_NONICKNAMEGIVEN );
	} else if (invalidNickname( nickname )) {
		return sendReply( data.fd, ERR_ERRONEUSNICKNAME );
	} else {
		if (!alreadyRegistered( nickname, data.fd )) {
			Server::setNicknameByFD( data.fd, nickname );
			//client nick set == true
		} else {
			return sendReply( ERR_WTF, data.fd );
		}
	}
}

/*	DLOU
Je dois check pour le oldnick et newnick car quand on se connect avec le meme nickname ca fout la merde
pour cluby: le nick set = true -> a voir ce que tu entendais par la, est-ce que c'est necessaire
*/

/* CLUBY
	NICK et USER fonctionne ensemble lors de la connection du client, si l'un a une erreur. 
	(Hors "already in use" parce que ca le change automatiquement avec une _ a la fin du nick proposer ? A voir si le client irssi le fait pas automatiquement de base, je ne suis plus sur de rien)
	L'autre ne peut etre bon, mais le server ne doit rien repondre. Donc pour moi la maniere dont j'ai penser pour le faire est un booleen
	lors de la connection pour NICK et USER et si les 2 booleen sont true on envoie le welcome message sinon rien.
*/

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