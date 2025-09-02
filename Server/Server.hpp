#pragma once

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <vector>
#include <map>

#include "Command.hpp"
#include "Client.hpp"
#include "NumReply.hpp"
#include "signal.hpp"

# define MAX_EVENTS 10
# define SERVER_VERSION "ft_irc-1.0"
# define USERMODES "itkol"

std::vector<std::string> extractMessages(std::string& buffer);

class Channel;

class Server
{
	private:
		Server( void );

		static std::string					_name;
		static std::string					_password;
		int									_socket;
		sockaddr_in							_address;
		int									_epoll;
		epoll_event							_event, _events[MAX_EVENTS];
		static Server						*_instance;
		std::map<int, Client>				_users;
		std::map< std::string, Channel >	_channels;

	public:
		std::string				datetime;

		void			loop();
		void			init( int port, std::string password );
		static Server*	getInstance( void );

		~Server();
		static void						destroyInstance( void );

		static std::map<int, Client>	getClients( void );
		static Client					*getClientByFD( const int fd );
		static const std::string&		getServername( void );
		static const std::string&		getServPass( void );
		static Channel					*getChannel( const std::string &name );

		void							addChannel( Channel& channel );
		void							delChannel( Channel& channel );
		bool							isChannelExist( const Channel& channel );
		bool							isChannelExist( const std::string& name );

		static void						setNicknameByFD( const int fd, const std::string& nickname );
		static void						setHostnameByFD( const int fd, const std::string& hostname );
		static void						setRealnameByFD( const int fd, const std::string& realname );
		static void						setUsernameByFD( const int fd, const std::string& username );
		static void						setServernameByFD( const int fd, const std::string& servername );

		static void						setPassByFD( const int fd, bool status );
		static void						setNickSetByFD( const int fd, bool status );
		static void						setUserSetByFD( const int fd, bool status );
		static void						setWelcomeStatusByFD( const int fd, bool status );
		static bool						isClientPass( const int fd );
		static bool						isClientRegistered( const int fd );
		static bool						isClientWelcomed( const int fd );
};
