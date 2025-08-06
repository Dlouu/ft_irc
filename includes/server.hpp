#pragma once

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include <cmath>
#include <map>
#include <vector>
#include <sstream>

#include "parsing.hpp"

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
