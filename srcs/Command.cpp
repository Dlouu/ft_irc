#include "Command.hpp"

Command* Command::_instance;

Command::Command() {
	init();
}

Command::~Command() {
	delete Command::_instance;
}

Command *Command::GetInstance( void ) {
    if (Command::_instance == NULL) {
        Command::_instance = new Command();
    }
    return Command::_instance;
}

void	Command::init( void ) {
	_command["KICK "]	=	&Command::kickCommand;
	_command["INVITE "]	=	&Command::inviteCommand;
	_command["TOPIC "]	=	&Command::topicCommand;
	_command["MODE "]	=	&Command::modeCommand;
	_command["CAP "]	=	&Command::capCommand;
	_command["NICK "]	=	&Command::nickCommand;
	_command["USER "]	=	&Command::userCommand;
	_command["PING "]	=	&Command::pingCommand;
	_command["PONG "]	=	&Command::pongCommand;
	_command["PRIVMSG "] =	&Command::privmsgCommand;
}

void	Command::notaCommand( void ) const {
	std::cout << "Not a command" << std::endl;
}

void	Command::handleCommand( const CommandData_t& data ) {
	std::string	key = data.message.substr(0, data.message.find(" ") + 1);

	if (_command.find(key) == _command.end()) {
		notaCommand();
	}
	else {
		(this->*_command[key])(data);
		std::cout << std::flush;
	}
	
	//voir si on fait un attr response
	/*
	faire un sigleton pour les commandes avec une fonction
	getInstance qui renvoie l'instance de la class Command
	Command::getInstance().handleCommand(command, fd);
	je pourrais le mettre dans le parsing et avoir acces au this
	constructeur en privé sinon on peut creer plusieurs instances
	*/

}


/*
NOTE Command
https://refactoring.guru/fr/design-patterns/Command/cpp/example
*/