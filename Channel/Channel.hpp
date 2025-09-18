#pragma once

#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include "Client.hpp"
#include "Server.hpp"

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
		Channel( const std::string &name );
		Channel						&operator=( const Channel &other );

		const std::string			&getName( void ) const;
		const std::string			&getTopic( void ) const;
		const std::string			&getPassword( void ) const;
		const bool					&isInviteOnly( void ) const;
		const unsigned long			&getUserLimit( void ) const;
		const std::vector< Client >	&getOperators( void ) const;
		const bool					&isTopicRestricted( void ) const;
		bool						isPasswordSet( void ) const;
		std::string					getChannelModes( void ) const;
		std::string					getChannelParams( void ) const;

		void						setInviteOnly( const bool state );
		void						setTopicRestricted( const bool state );
		void						setUserLimit( const unsigned long n );
		void						setPassword( const std::string password );
		void						setTopic( const Client &executor, const std::string topic );

		void						addUser( const Client &executor, Client &target );
		void						addUser( const Server &server, Client &target );
		void						delUser( const Client &executor, Client &target );
		void						delUser(Client& target);

		void						addOperator( const Client &executor, const Client &target );
		void						addOperator( const Server &server, const Client &target );
		void						delOperator( const Client &executor, const Client &target );

		bool						isClientUser( const Client &target );
		bool						isClientOperator( const Client &target );
		bool						isPasswordCorrect( const std::string &password ) const;

		void						shareMessage( const std::string &msg );
		void						shareMessage( const Client &executor, const std::string &rawMsg, const std::string &cmd, std::string reason );
		void						shareMessage( const Client &executor, const Client &target, const std::string &rawMsg, const std::string &cmd );
		void						shareMessage( const Client &executor, const std::string &rawMsg, const std::string &cmd );
};

std::ostream	&operator<<( std::ostream &os, const Channel &add );
