#include "Client.hpp"

Client::Client() {
}

Client::~Client() {
}

void	Client::setNickname( std::string str ) {
	this->_nickname = str;
}

void	Client::setUserInfo( std::string str ) {
	( void )str;
}

std::string	Client::getNickname( void ) const {
	return ( this->_nickname );
}

std::string	Client::getUsername( void ) {
	return ( this->_username );
}

std::string	Client::getHostname( void ) {
	return ( this->_hostname );
}
std::string	Client::getServername( void ) {
	return ( this->_servername );
}

std::string	Client::getRealname( void ) {
	return ( this->_realname );
}
