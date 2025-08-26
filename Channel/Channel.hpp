/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 08:18:40 by tclaereb          #+#    #+#             */
/*   Updated: 2025/08/26 17:37:42 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include "../Client/Client.hpp"
#include "../Server/Server.hpp"

class Server;

class Channel {
	private:
		std::string				_name;
		std::string				_topic;
		std::string				_password;
		unsigned long			_userLimit;

		std::vector< Client >	_users;
		std::vector< Client >	_operators;

		bool					_inviteOnly;
		bool					_topicOperatorOnly;

	public:
		Channel( void );
		Channel( const std::string &name, const std::string &pass );
		Channel						&operator=( const Channel &other );

		const std::string			&getName( void ) const;
		const bool					&getInviteOnly( void ) const;
		const unsigned long			&getUserLimit( void ) const;
		const std::vector< Client >	&getOperators( void ) const;

		void						setInviteOnly( const bool state );
		void						setUserLimit( const unsigned long n );
		void						setPassword( const std::string password );
		void						setTopic( const Client &executor, const std::string topic );

		void						addUser( const Client &executor, const Client &target );
		void						addUser( const Server &server, const Client &target );
		void						delUser( const Client &executor, const Client &target );

		void						addOperator( const Client &executor, const Client &target );
		void						addOperator( const Server &server, const Client &target );
		void						delOperator( const Client &executor, const Client &target );

		bool						isClientUser( const Client &target );
		bool						isClientOperator( const Client &target );
		bool						isPasswordCorrect( const std::string &password ) const;

		void						shareMessage( const Client &executor, const std::string &rawMsg );
};

std::ostream	&operator<<( std::ostream &os, const Channel &add );
