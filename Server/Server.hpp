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

#include "../Command/Command.hpp"
#include "../Client/Client.hpp"
#include "../NumReply/NumReply.hpp"
#include "signal.hpp"

# define MAX_EVENTS 10
# define SERVER_VERSION "ft_irc-1.0"
# define USERMODES "itkol"

std::vector<std::string> extractMessages(std::string& buffer);

class Server
{
	private:
		Server( void );
		static std::string		_name;
		int						_socket;
		sockaddr_in				_address;
		int						_epoll;
		epoll_event				_event, _events[MAX_EVENTS];
		static Server			*_instance;
		std::map<int, Client>	_users;
		
	public:
		std::string				datetime;

		void			loop();
		void			init( int port );
		static Server*	getInstance( void );

		~Server();
		static void						destroyInstance( void );
	
		static std::map<int, Client>	getClients( void );
		static Client					getClientByFD( const int fd );
		static const std::string&		getServername( void );

		static void						setNicknameByFD( const int fd, const std::string& nickname );
		static void						setHostnameByFD( const int fd, const std::string& hostname );
		static void						setRealnameByFD( const int fd, const std::string& realname );
		static void						setUsernameByFD( const int fd, const std::string& username );
		static void						setServernameByFD( const int fd, const std::string& servername );
		static void						setNickSetByFD( const int fd, bool status );
		static void						setUserSetByFD( const int fd, bool status );
		static bool						isUserRegistered( const int fd );
};
