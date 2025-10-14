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
	_command[ "INVITE " ]	=	&Command::inviteCommand;
	_command[ "JOIN " ]		= 	&Command::joinCommand;
	_command[ "KICK " ]		=	&Command::kickCommand;
	_command[ "MODE " ]		=	&Command::modeCommand;
	_command[ "NICK " ]		=	&Command::nickCommand;
	_command[ "PART " ]		=	&Command::partCommand;
	_command[ "PASS " ]		=	&Command::passCommand;
	_command[ "PING " ]		=	&Command::pingCommand;
	_command[ "PRIVMSG " ]	=	&Command::privmsgCommand;
	_command[ "TOPIC " ]	=	&Command::topicCommand;
	_command[ "USER " ]		=	&Command::userCommand;
	_command[ "QUIT " ]		=	&Command::quitCommand;
}

void	Command::notaCommand( void ) const {
	return ;
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

	std::string cleanMessage = message;
	if ( cleanMessage.size() >= 2 && cleanMessage.substr( cleanMessage.size() - 2 ) == "\r\n" ) {
		cleanMessage = cleanMessage.substr( 0, cleanMessage.size() - 2 );
	}
	LOGC( CLIENT ) << cleanMessage;
	getInstance()->handleCommand( ( CommandData_t ){ cleanMessage, fd } );
}

std::vector< std::string > Command::split( const std::string &str, const char delimiter ) const {
	std::vector< std::string >	container;
	std::string					token;
	std::istringstream			iss( str );

	while( std::getline( iss, token, delimiter ) ) {
		if ( !token.empty() )
			container.push_back( token );
	}

	return ( container );
}
