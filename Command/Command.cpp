#include "Command.hpp"

Command* Command::_instance;

Command::Command() {
	init();
}

Command::~Command() {
}

Command *Command::getInstance( void ) {
    if ( Command::_instance == NULL ) {
        Command::_instance = new Command();
    }
    return Command::_instance;
}

void	Command::init( void ) {
	_command[ "KICK " ]		=	&Command::kickCommand;
	_command[ "INVITE " ]	=	&Command::inviteCommand;
	_command[ "TOPIC " ]	=	&Command::topicCommand;
	_command[ "MODE " ]		=	&Command::modeCommand;
	_command[ "NICK " ]		=	&Command::nickCommand;
	_command[ "USER " ]		=	&Command::userCommand;
	_command[ "PING " ]		=	&Command::pingCommand;
	_command[ "PRIVMSG " ]	=	&Command::privmsgCommand;
	_command[ "JOIN " ]		= 	&Command::joinCommand;
}

void	Command::notaCommand( void ) const {
	// std::cout << RED "Not a command" END << std::endl;
}

void	Command::handleCommand( const CommandData_t& data ) {
	std::string	key = data.message.substr( 0, data.message.find( " " ) + 1 );

	if ( _command.find( key ) == _command.end() ) {
		notaCommand();
	} else {
		( this->*_command[ key ] )( data );
		std::cout << std::flush;
	}
}

void Command::processIRCMessage( int fd, const std::string& message ) {

	std::cout << YEL ">>> " PUR << message << END;

	std::string cleanMessage = message;
	if ( cleanMessage.size() >= 2 && cleanMessage.substr( cleanMessage.size() - 2 ) == "\r\n" ) {
		cleanMessage = cleanMessage.substr( 0, cleanMessage.size() - 2 );
	}
	LOGC( INFO ) << message;
	getInstance()->handleCommand( ( CommandData_t ){ cleanMessage, fd } );
}

std::vector< std::string > Command::split( const std::string &str, const char delimiter ) const {
	std::vector< std::string >	container;
	std::string					token;
	std::istringstream			iss( str );

	while( std::getline( iss, token, delimiter ) ) {
		container.push_back( token );
	}

	return ( container );
}

//We need to check if it's the client is connected already. By checking if NICK and USER have been successful
//Only after that we send the Welcome MOTD
