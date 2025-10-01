#include "Client.hpp"

unsigned int	Client::maxChannel = 5;

Client::Client() :	_nickSet( false ),
					_userSet( false ),
					_welcomed( false ),
					_isPassOk( false ),
					_nickname( "" ),
					_username( "" ),
					_hostname( "" ),
					_servername( "" ),
					_realname( "" ),
					_fd (-1),
					_channels() {}

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

void	Client::setFD( const int &fd ) {
	this->_fd = fd;
}

void	Client::setChannels( const std::string& chan) {
	this->_channels.push_back(chan);
}

void	Client::delChannel(const std::string& chan) {
	for (std::vector<std::string>::iterator it = this->_channels.begin(); it != this->_channels.end(); ++it) {
		if (*it == chan) {
			this->_channels.erase(it);
			return;
		}
	}
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

const std::vector<std::string>&	Client::getChannels( void ) const {
	return (this->_channels);
}

const std::string	Client::getMask( void ) const {
	std::string mask = this->_nickname + "!" + this->_username + "@" + this->_hostname;
	return ( mask );
}

void	Client::setPass( bool status ) {
	this->_isPassOk = status;
}

// Nick and User Set Status
void	Client::setNickSet( bool status ) {
	this->_nickSet = status;
}

void	Client::setUserSet( bool status ) {
	this->_userSet = status;
}

void	Client::setWelcomeStatus( bool status ) {
	this->_welcomed = status;
}

bool	Client::isPassOk( void ) {
	return ( this->_isPassOk );
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

void	Client::shareMessage( const Client &executor, const std::string &rawMsg ) {
	std::string	msg = ":" + executor.getMask() + " PRIVMSG " + this->_nickname + " :" + rawMsg + "\r\n";
	send( this->getFD(), msg.c_str(), msg.size(), 0 );
	LOGC( SERVER ) << msg;
}


bool	Client::operator==( const Client &other ) const {
	return ( this->getMask() == other.getMask() );
}
