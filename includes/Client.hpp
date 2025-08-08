#pragma once

#include <string>
#include <iostream>
#include <netinet/in.h>
#include <map>

class Client
{
	private:
		std::string	nickname;
		std::string	username;
		std::string	hostname;
		std::string	servername;
		std::string	realname;
		int			fd;
	
		static Client*	_instance;

		Client();
		~Client();
		
	public:
	
		static Client*	GetInstance( void );
};