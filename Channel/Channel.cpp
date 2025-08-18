/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:31:21 by tclaereb          #+#    #+#             */
/*   Updated: 2025/08/18 13:16:45 by tclaereb         ###   ########.fr       */
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

const std::vector< int >	&Channel::getOperators( void ) const {
	return ( this->_operators );
}

void	Channel::setInviteOnly( const bool state ) {
	this->_inviteOnly = state;
}

void	Channel::setUserLimit( const unsigned long n ) {
	this->_userLimit = n;
}

void	Channel::setPassword( const std::string password ) {
	// alpha numeric only
	this->_password = password;
}

void	Channel::addOperator( const int fd ) {
	if ( fd <= 1 )
		return ;

	std::vector< int >::iterator it = std::find( this->_operators.begin(), this->_operators.end(), fd );

	if ( it != this->_operators.end() )
		return ;

	this->_operators.push_back( fd );
}

void	Channel::delOperator( const int fd ) {
	std::vector< int >::iterator it = std::find( this->_operators.begin(), this->_operators.end(), fd );

	if ( it == this->_operators.end() )
		return ;

	this->_operators.erase( it );
}
