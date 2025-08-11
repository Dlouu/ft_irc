#pragma once

#include <map>
#include <string>
#include <iostream>

class Client
{
	private:
		std::string	_nickname;
		std::string	_username;
		std::string	_hostname;
		std::string	_servername;
		std::string	_realname;

	public:
		Client();
		~Client();

		void		setNickname( std::string str );
		void		setUserInfo( std::string str );
		std::string	getNickname( void );
		std::string	getUsername( void );
		std::string	getHostname( void );
		std::string	getServername( void );
		std::string	getRealname( void );
};
