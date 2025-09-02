#pragma once

#include <map>
#include <string>
#include <iostream>

class Client
{
	private:
		bool		_nickSet;
		bool		_userSet;
		bool		_welcomed;
		bool		_isPassOk;
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
		void				setUsername( const std::string& str );
		void				setServername( const std::string& str );
		void				setHostname( const std::string& str );
		void				setRealname( const std::string& str );
		void				setFD( const int &fd );
		
		void				setPass(bool status);
		void				setNickSet( bool status );
		void				setUserSet( bool status );
		void				setWelcomeStatus( bool status );

		const std::string&	getNickname( void ) const;
		const std::string&	getUsername( void ) const;
		const std::string&	getHostname( void ) const;
		const std::string&	getServername( void ) const;
		const std::string&	getRealname( void ) const;
		const std::string	getMask( void ) const;
		const int&			getFD( void ) const;

		bool				isPassOk( void );
		bool				isNickSet( void );
		bool				isUserSet( void );
		bool				isWelcomed( void );

		bool				operator==( const Client &other ) const;
};
