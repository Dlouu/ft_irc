#include "Command.hpp"
#include "Colors.hpp"

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
	std::cout << RED "Not a command" END << std::endl;
}

void	Command::handleCommand( const CommandData_t& data ) {
	std::string	key = data.message.substr(0, data.message.find(" ") + 1);

	if (_command.find(key) == _command.end()) {
		notaCommand();
	} else {
		(this->*_command[key])(data);
		std::cout << std::flush;
	}
}
