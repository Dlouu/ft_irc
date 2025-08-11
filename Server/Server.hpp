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
		int						_socket;
		sockaddr_in				_address;
		int						_epoll;
		epoll_event				_event, _events[MAX_EVENTS];
		static Server			*_instance;
		
		Server( void );

		
		public:
		~Server();
		std::map<int, Client>	_users;
		void			loop();
		void			init( int port );
		static Server*	GetInstance( void );
		static void		DestroyInstance( void );
};
