#include "Channel.hpp"

Channel::Channel( void ) : _name( "" ), _password( "" ), _userLimit( 100 ), _inviteOnly( false ), _topicOperatorOnly( true ) {}

Channel::Channel( const std::string &name ) :
		_name( name ), _topic( "" ), _password( "" ), _userLimit( 100 ), _inviteOnly( false ), _topicOperatorOnly( true ) {}

const std::string	&Channel::getName( void ) const {
	return ( this->_name );
}

const std::string	&Channel::getTopic( void ) const {
	return ( this->_topic );
}

std::vector< Client >	Channel::getUsers( void ) const {
	return ( this->_users );
}

const std::string	&Channel::getPassword( void ) const {
	return ( this->_password );
}

const bool	&Channel::isInviteOnly( void ) const {
	return ( this->_inviteOnly );
}

const bool	&Channel::isTopicRestricted( void ) const {
	return ( this->_topicOperatorOnly );
}

bool	Channel::isPasswordSet( void ) const {
	if (this->_password == "")
		return ( false );
	return ( true );
}

std::string	Channel::getChannelModes( void ) const {
	std::string	modes = "";
	if (this->isInviteOnly())
		modes.append("i");
	if (this->isTopicRestricted())
		modes.append("t");
	if (this->getUserLimit() > 0)
		modes.append("l");
	if (this->isPasswordSet())
		modes.append("k");
	return ( modes );
}

std::string	Channel::getChannelParams( void ) const {
	std::stringstream	params;
	if (this->getUserLimit() > 0) {
		params << _userLimit;
		if (this->isPasswordSet()) {
			params << " " << _password;
		}
	}
	else if (this->isPasswordSet()) {
		params << _password;
	}
	return ( params.str() );
}

const unsigned long	&Channel::getUserLimit( void ) const {
	return ( this->_userLimit );
}

unsigned long Channel::getUserCount( void ) const {
	return ( this->_users.size() );
}

const std::vector< Client >	&Channel::getOperators( void ) const {
	return ( this->_operators );
}

void	Channel::setInviteOnly( const bool state ) {
	this->_inviteOnly = state;
}

void	Channel::setTopicRestricted( const bool state ) {
	this->_topicOperatorOnly = state;
}

void	Channel::setUserLimit( const unsigned long n ) {
	this->_userLimit = n;
}

void	Channel::setPassword( const std::string password ) {
	if ( password == "x" )
		return ;

	for ( std::size_t i = 0; i < password.size(); i++ ) {
		if ( !std::isalnum( password[ i ] ) )
			return ;
	}
	this->_password = password;
}

void	Channel::setTopic( const std::string topic ) {
	this->_topic = topic;
}


void	Channel::addUser( Client &target ) {
	if ( this->isClientUser( target ) )
		return ;

	this->delInvitation( target );
	this->_users.push_back( target );
	target.setChannels( this->_name );

	this->shareMessage(":" + target.getMask() + " JOIN " + this->_name + "\r\n");
}

void	Channel::delUser( Client &target ) {
	std::vector< Client >::iterator it = std::find(this->_users.begin(), this->_users.end(), target );
	this->delOperator( target );

	if ( it == this->_users.end() )
		return ;
	this->shareMessage( ":" + target.getMask() + " PART " + this->_name + " " + g_vars[ "reason" ] + "\r\n" );
	this->_users.erase( it );
	target.delChannel( this->_name );

	if ( this->_users.size() < 1 )
		Server::delChannel( *this );
}

void	Channel::addOperator( Client &target ) {
	if ( this->isClientOperator( target ) )
		return ;

	this->_operators.push_back( target );
}

void	Channel::delOperator( Client &target ) {
	if ( !this->isClientOperator( target ) )
		return ;

	std::vector< Client >::iterator it = std::find( this->_operators.begin(), this->_operators.end(), target );

	if ( it == this->_operators.end() )
		return ;

	this->_operators.erase( it );
}

void	Channel::inviteSomeone( Client &target ) {
	if ( this->hasAnInvitation( target ) )
		return ;

	this->_invits.push_back( target );
}

void	Channel::delInvitation( Client &target ) {
	if ( !this->hasAnInvitation( target ) )
		return ;

	std::vector< Client >::iterator it = std::find( this->_invits.begin(), this->_invits.end(), target );

	if ( it == this->_invits.end() )
		return ;

	this->_invits.erase( it );
}

bool	Channel::hasAnInvitation( const Client &target ) {
	std::vector< Client >::iterator it = std::find( this->_invits.begin(), this->_invits.end(), target );

	if ( it == this->_invits.end() )
		return ( false );
	return ( true );
}

bool	Channel::isClientUser( const Client &target ) {
	std::vector< Client >::iterator it = std::find( this->_users.begin(), this->_users.end(), target );

	if ( it == this->_users.end() )
		return ( false );
	return ( true );
}

bool	Channel::isClientOperator( const Client &target ) {
	std::vector< Client >::iterator it = std::find( this->_operators.begin(), this->_operators.end(), target );

	if ( it == this->_operators.end() )
		return ( false );
	return ( true );
}

bool	Channel::isClientBan( const Client &target ) {
	std::vector< Client >::iterator it = std::find( this->_bans.begin(), this->_bans.end(), target );

	if ( it == this->_bans.end() )
		return ( false );
	return ( true );
}

bool	Channel::isPasswordCorrect( const std::string &password ) const {
	if ( password == this->_password || password == "x" )
		return ( true );
	return ( false );
}

void	Channel::Welcome( const Client &client ) {
	std::string	clientListMsg = "";
	for ( unsigned int i = 0; i < this->_users.size(); i++ ) {
		Client	&it = this->_users[ i ];
		clientListMsg += ( this->isClientOperator( it ) ? "@" : "" ) + this->_users[ i ].getNickname() + ( i == this->_users.size() - 1 ? "" : " " );
	}

	g_vars[ "channel" ] = this->getName();
	g_vars[ "names" ] = clientListMsg;

	sendReply( client.getFD(), RPL_NAMREPLY );
	sendReply( client.getFD(), RPL_ENDOFNAMES );

	g_vars[ "topic" ] = this->_topic;
	sendReply( client.getFD(), RPL_TOPIC );
}

void	Channel::shareMessage( const Client &executor, const Client &target, const std::string &rawMsg, const std::string &cmd ) {
	std::string	msg = ":" + executor.getMask() + " " + cmd + " " + this->_name + " :" + rawMsg;
	LOGC( SERVER ) << msg;
	msg += "\r\n";
	send( target.getFD(), msg.c_str(), msg.size(), MSG_DONTWAIT );
}

void	Channel::shareMessage( const Client &executor, const std::string &rawMsg, const std::string &cmd ) {
	for ( size_t i = 0; i < this->_users.size(); i++ ) {
		if ( cmd == "PRIVMSG" && executor.getFD() == this->_users[ i ].getFD() )
			continue ;
		std::string	msg = ":" + executor.getMask() + " " + cmd + " " + this->_name + " :" + rawMsg;
		LOGC( SERVER ) << msg;
		msg += "\r\n";
		send( this->_users[ i ].getFD(), msg.c_str(), msg.size(), MSG_DONTWAIT );
	}
}

void	Channel::shareMessage( const Client &executor, const std::string &rawMsg, const std::string &cmd, std::string reason ) {
	for ( size_t i = 0; i < this->_users.size(); i++ ) {
		std::string	msg = ":" + executor.getMask() + " " + cmd + " " + this->_name + " " + rawMsg + " :" + reason;
		LOGC( SERVER ) << msg;
		msg += "\r\n";
		send( this->_users[ i ].getFD(), msg.c_str(), msg.size(), MSG_DONTWAIT );
	}
}

void	Channel::shareMessage( const std::string &msg ) {
	for ( size_t i = 0; i < this->_users.size(); i++ ) {
		send( this->_users[ i ].getFD(), msg.c_str(), msg.size(), MSG_DONTWAIT );
		LOGC( SERVER ) << ( msg[ msg.length() - 1 ] == '\n' ? msg.substr( 0, msg.length() - 2 ) : msg );
	}
}

Channel	&Channel::operator=( const Channel &other ) {
	this->_name = other._name;
	this->_topic = other._topic;
	this->_password = other._password;
	this->_userLimit = other._userLimit;
	this->_users = other._users;
	this->_operators = other._operators;
	this->_inviteOnly = other._inviteOnly;
	this->_topicOperatorOnly = other._topicOperatorOnly;
	return ( *this );
}

bool	Channel::operator==( const Channel &other ) const {
	return ( this->_name == other._name );
}

std::ostream	&operator<<( std::ostream &os, const Channel &add ) {
	os << "Channel name: " << add.getName();
	return ( os );
}
