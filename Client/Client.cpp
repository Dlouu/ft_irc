#include "Client.hpp"

Client::Client() :	_nickSet( false ),
					_userSet( false ),
					_welcomed( false ),
					_nickname( "" ),
					_username( "" ),
					_hostname( "" ),
					_servername( "" ),
					_realname( "" ) {}

Client::~Client() {}

void	Client::setNickname( const std::string& str ) {
	this->_nickname = str;
}

void	Client::setUsername( const std::string& str ) {
	this->_username = str;
}

void	Client::setServername( const std::string& str ) {
	this->_servername = str;
}

void	Client::setHostname( const std::string& str ) {
	this->_hostname = str;
}

void	Client::setRealname( const std::string& str ) {
	this->_realname = str;
}

const std::string&	Client::getNickname( void ) {
	return ( this->_nickname );
}

const std::string&	Client::getUsername( void ) {
	return ( this->_username );
}

const std::string&	Client::getHostname( void ) {
	return ( this->_hostname );
}
const std::string&	Client::getServername( void ) {
	return ( this->_servername );
}

const std::string&	Client::getRealname( void ) {
	return ( this->_realname );
}

// Nick and User Set Status
void	Client::setNickSet( bool status ) {
	this->_nickSet = status;
}

void	Client::setUserSet( bool status ) {
	this->_userSet = status;
}

void	Client::SetWelcomeStatus( bool status ) {
	this->_welcomed = status;
}

bool	Client::isNickSet( void ) {
	return ( this->_nickSet );
}

bool	Client::isUserSet( void ) {
	return ( this->_userSet );
}

bool	Client::isWelcomed( void ) {
	return ( this->_welcomed );
}
