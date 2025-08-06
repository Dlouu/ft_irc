#include "command.hpp"

Command::Command() {
	//faire le tableau de commandes ici
}

Command::~Command() {
	//laisser en public et delete tous les new
	//faudra l'appeler dans le main
}

void	Command::kickCommand( void ) const {
	std::cout << "KICK command called" << std::endl;
}

void	Command::inviteCommand( void ) const {
	std::cout << "INVITE command called" << std::endl;
}

void	Command::topicCommand( void ) const {
	std::cout << "TOPIC command called" << std::endl;
}

void	Command::modeCommand( void ) const {
	std::cout << "MODE command called" << std::endl;
}

void	Command::capCommand( void ) const {
	std::cout << "CAP command called" << std::endl;
}

void	Command::nickCommand( void ) const {
	std::cout << "NICK command called" << std::endl;
}

void	Command::userCommand( void ) const {
	std::cout << "USER command called" << std::endl;
}

void	Command::privmsgCommand( void ) const {
	std::cout << "PRIVMSG command called" << std::endl;
}

void	Command::pingCommand( void ) const {
	std::cout << "PING command called" << std::endl;
}

void	Command::pongCommand( void ) const {
	std::cout << "PONG command called" << std::endl;
}

void	Command::joinCommand( void ) const {
	std::cout << "JOIN command called" << std::endl;
}
/*
A mettre dans des fichiers separes dans un dossier commands
Faut aue je fasse le tableau dans le constructeur et que je le passe en param
mettre la class dans le main pour que ca cree les tab qu'une fois
*/
void	Command::handleCommand( std::string cleanMessage, int fd ) {
	std::string	command = "";
	std::string commands[10] = {	"KICK ",
									"INVITE ",
									"TOPIC ",
									"MODE ",
									"CAP ",
									"NICK ",
									"USER ",
									"PING ",
									"PONG ",
									"PRIVMSG "};
	void	(Command::*fPtr[10])(void) const = {	&Command::kickCommand,
													&Command::inviteCommand,
													&Command::topicCommand,
													&Command::modeCommand,
													&Command::capCommand,
													&Command::nickCommand,
													&Command::userCommand,
													&Command::pingCommand,
													&Command::pongCommand,
													&Command::privmsgCommand};
	for (int i = 0; i < 8; i++) {
		command = cleanMessage.substr(0, cleanMessage.find(" ") + 1);
		if (command == commands[i]) {
			(this->*fPtr[i])();
		return ;
		}
	}
	// _notaCommand(command);
	//voir si on fait un attr response
	/*
	faire un sigleton pour les commandes avec une fonction
	getInstance qui renvoie l'instance de la class Command
	Command::getInstance().handleCommand(command, fd);
	je pourrais le mettre dans le parsing et avoir acces au this
	constructeur en privé sinon on peut creer plusieurs instances
	*/
	std::string response;
	if (cleanMessage == "CAP LS") {
		response = "CAP * LS :\r\n";
		std::cout << "<<< " << response;
		send(fd, response.c_str(), response.length(), 0);
	}
	else if (cleanMessage.find("NICK ") == 0) {
		std::string nickname;
		nickname = cleanMessage.substr(5, cleanMessage.length());
		std::cout << "NICK=" << nickname << std::endl;
	}
	else if (cleanMessage.find("USER ") == 0) {
		std::string user;
		user = cleanMessage.substr(5, cleanMessage.length());
		std::cout << "USER=" << user << std::endl;
	}
}


/*
NOTE SINGLETON
https://refactoring.guru/fr/design-patterns/singleton/cpp/example
*/