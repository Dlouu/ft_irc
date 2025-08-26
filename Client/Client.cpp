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

void	Client::setFD( const int &fd ) {
	this->_fd = fd;
}

const std::string&	Client::getNickname( void ) const {
	return ( this->_nickname );
}

const std::string&	Client::getUsername( void ) const {
	return ( this->_username );
}

const std::string&	Client::getHostname( void ) const {
	return ( this->_hostname );
}
const std::string&	Client::getServername( void ) const {
	return ( this->_servername );
}

const std::string&	Client::getRealname( void ) const {
	return ( this->_realname );
}

const int&	Client::getFD( void ) const {
	return ( this->_fd );
}

const std::string	Client::getMask( void ) const {
	std::string mask = this->_nickname + "!" + this->_username + "@" + this->_hostname;
	return ( mask );
}

bool	Client::operator==( const Client &other ) const {
	return ( this->getMask() == other.getMask() );
}
