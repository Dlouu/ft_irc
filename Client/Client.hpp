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

		void				setNickname( const std::string& str );
		void				setUserInfo( const std::string& str );
		const std::string&	getNickname( void );
		const std::string&	getUsername( void );
		const std::string&	getHostname( void );
		const std::string&	getServername( void );
		const std::string&	getRealname( void );
};
