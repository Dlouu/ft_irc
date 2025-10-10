#pragma once

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sys/types.h>
#include <sys/socket.h>
#include "Log.hpp"

class Client
{
	private:
		bool								_nickSet;
		bool								_userSet;
		bool								_welcomed;
		bool								_isPassOk;
		std::string							_nickname;
		std::string							_username;
		std::string							_hostname;
		std::string							_servername;
		std::string							_realname;
		int									_fd;
		std::vector<std::string>			_channels;

	public:
		static unsigned int maxChannel;

		Client();
		~Client();

		void							setNickname( const std::string& str );
		void							setUsername( const std::string& str );
		void							setServername( const std::string& str );
		void							setHostname( const std::string& str );
		void							setRealname( const std::string& str );
		void							setFD( const int &fd );
		void							setPass(bool status);
		void							setChannels( const std::string& chan);
		void							delChannel(const std::string& chan);

		void							setNickSet( bool status );
		void							setUserSet( bool status );
		void							setWelcomeStatus( bool status );

		const std::string&				getNickname( void ) const;
		const std::string&				getUsername( void ) const;
		const std::string&				getHostname( void ) const;
		const std::string&				getServername( void ) const;
		const std::string&				getRealname( void ) const;
		const std::string				getMask( void ) const;
		const int&						getFD( void ) const;
		const std::vector<std::string>&	getChannels( void ) const;

		bool							isPassOk( void );
		bool							isNickSet( void );
		bool							isUserSet( void );
		bool							isWelcomed( void );

		void							shareMessage( const Client &executor, const std::string &rawMsg );

		bool							operator==( const Client &other ) const;
};
