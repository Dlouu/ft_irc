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
#include <vector>
#include <map>

#include "./../Command/Command.hpp"
#include "./../Client/Client.hpp"
#include "signal.hpp"

# define MAX_EVENTS 10

std::vector<std::string> extractMessages(std::string& buffer);

class Server
{
	private:
		Server( void );
		int						_socket;
		sockaddr_in				_address;
		int						_epoll;
		epoll_event				_event, _events[MAX_EVENTS];
		static Server			*_instance;
		std::map<int, Client>	_users;

	public:
		void			loop();
		void			init( int port );
		static Server*	GetInstance( void );
		~Server();

		static void		DestroyInstance( void );
		static	std::map< int, Client > GetClients( void );
		static	Client	GetClientByFD( const int fd );
		static	Client	GetClientByNickname( const std::string nickname );
};
