#include "Client.hpp"

Client::Client() {
}

Client::~Client() {
}

void	Client::setNickname( const std::string& str ) {
	this->_nickname = str;
}

void	Client::setUserInfo( const std::string& str ) {
	( void )str;
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
