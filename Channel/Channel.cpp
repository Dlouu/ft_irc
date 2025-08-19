/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:31:21 by tclaereb          #+#    #+#             */
/*   Updated: 2025/08/19 15:05:49 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel( const std::string &name, const std::string &pass ) :
		_name( name ), _topic( "" ), _password( pass ), _userLimit( 0 ), _inviteOnly( false ), _topicOperatorOnly( true ) {}

const std::string	&Channel::getName( void ) const {
	return ( this->_name );
}

const bool	&Channel::getInviteOnly( void ) const {
	return ( this->_inviteOnly );
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

void	Channel::addOperator( const Client &executor, const Client &target ) {
	if ( this->isClientOperator( executor ) && !this->isClientOperator( target ) )
		this->_operators.push_back( target );
}

void	Channel::delOperator( const Client &executor, const Client &target ) {
	if ( this->isClientOperator( executor ) && !this->isClientOperator( target ) )
		return ;

	std::vector< Client >::iterator it = std::find( this->_operators.begin(), this->_operators.end(), target );
	this->_operators.erase( it );
}

bool	Channel::isClientOperator( const Client &target ) {
	std::vector< Client >::iterator it = std::find( this->_operators.begin(), this->_operators.end(), target );

	if ( it == this->_operators.end() )
		return ( false );
	return ( true );
}
