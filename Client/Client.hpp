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
		int			_fd;

	public:
		Client();
		~Client();

		void				setNickname( const std::string& str );
		void				setUserInfo( const std::string& str );
		void				setFD( const int &fd );
		const std::string&	getNickname( void ) const;
		const std::string&	getUsername( void ) const;
		const std::string&	getHostname( void ) const;
		const std::string&	getServername( void ) const;
		const std::string&	getRealname( void ) const;
		const std::string	getMask( void ) const;
		const int&			getFD( void ) const;

		bool				operator==( const Client &other ) const;
};
