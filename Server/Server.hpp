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

# define MAX_EVENTS 10 

std::vector<std::string> extractMessages(std::string& buffer);

class Server
{
	private:
		int	_socket;
		sockaddr_in	_address;
		int _epoll;
		epoll_event _event, _events[MAX_EVENTS];

	public:
		Server(int port);
		~Server();
		void loop();
};
