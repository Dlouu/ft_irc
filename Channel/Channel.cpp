/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:31:21 by tclaereb          #+#    #+#             */
/*   Updated: 2025/09/08 23:26:43 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel( void ) : _name( "" ), _password( "" ), _userLimit( 0 ), _inviteOnly( false ), _topicOperatorOnly( true ) {}

Channel::Channel( const std::string &name, const std::string &pass ) :
		_name( name ), _topic( "" ), _password( pass ), _userLimit( 0 ), _inviteOnly( false ), _topicOperatorOnly( true ) {}

const std::string	&Channel::getName( void ) const {
	return ( this->_name );
}

const std::string	&Channel::getPassword( void ) const {
	return ( this->_password );
}

const bool	&Channel::getInviteOnly( void ) const {
	return ( this->_inviteOnly );
}

const bool	&Channel::getTopicRestricted( void ) const {
	return ( this->_topicOperatorOnly );
}

bool	Channel::getPasswordStatus( void ) const {
	if (this->_password == "")
		return ( false );
	return ( true );
}

std::string	Channel::getChannelModes( void ) const {
	std::string	modes = "";
	if (this->getInviteOnly())
		modes.append("i");
	if (this->getTopicRestricted())
		modes.append("t");
	if (this->getUserLimit() > 0)
		modes.append("l");
	if (this->getPasswordStatus())
		modes.append("k");
	return ( modes );
}

std::string	Channel::getChannelParams( void ) const {
	std::stringstream	params;
	if (this->getUserLimit() > 0) {
		params << _userLimit;
		if (this->getPasswordStatus()) {
			params << " " << _password;
		}
	}
	else if (this->getPasswordStatus()) {
		params << _password;
	}
	return ( params.str() );
}

const unsigned long	&Channel::getUserLimit( void ) const {
	return ( this->_userLimit );
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
	for ( std::size_t i = 0; i < password.size(); i++ ) {
		if ( !std::isalnum( password[ i ] ) )
			return ;
	}
	this->_password = password;
}

void	Channel::setTopic( const Client &executor, const std::string topic ) {
	if ( !this->isClientOperator( executor ) && this->_topicOperatorOnly )
		return ;

	this->_topic = topic;
}

void	Channel::addUser( const Client &executor, const Client &target ) {
	if ( this->isClientOperator( executor ) && !this->isClientUser( target ) )
		this->_users.push_back( target );
}

void	Channel::addUser( const Server &server, const Client &target ) {
	( void )server;
	if ( !this->isClientUser( target ) ) {
		this->_users.push_back( target );
	}
}

void	Channel::delUser( const Client &executor, const Client &target ) {
	if ( !this->isClientOperator( executor ) || this->isClientUser( target ) )
		return;

	std::vector< Client >::iterator it = std::find(this->_users.begin(), this->_users.end(), target );
	this->_users.erase( it );
}

void	Channel::addOperator( const Client &executor, const Client &target ) {
	if ( this->isClientOperator( executor ) && !this->isClientOperator( target ) )
		this->_operators.push_back( target );
}

void	Channel::addOperator( const Server &server, const Client &target ) {
	( void ) server;
	if ( !this->isClientOperator( target ) ) {
		this->_operators.push_back( target );
	}
}

void	Channel::delOperator( const Client &executor, const Client &target ) {
	if ( !this->isClientOperator( executor ) || this->isClientOperator( target ) )
		return ;

	std::vector< Client >::iterator it = std::find( this->_operators.begin(), this->_operators.end(), target );
	this->_operators.erase( it );
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

bool	Channel::isPasswordCorrect( const std::string &password ) const {
	if ( password == this->_password and this->_password != "x" )
		return ( true );
	return ( false );
}

void	Channel::shareMessage( const Client &executor, const std::string &rawMsg ) {
	for ( size_t i = 0; i < this->_users.size(); i++ ) {
		LOGC( INFO ) << "Hello";
		// if ( executor.getFD() == this->_users[ i ].getFD() )
		// 	continue ;
		( void )executor;
		std::string	msg = ":" + this->_users[ i ].getMask() + " PRIVMSG " + this->_name + " :" + rawMsg;
		send( this->_users[ i ].getFD(), msg.c_str(), msg.size(), 0 );
		LOGC( INFO ) << msg;
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

std::ostream	&operator<<( std::ostream &os, const Channel &add ) {
	os << "Channel name: " << add.getName() << "\n";
	return ( os );
}
