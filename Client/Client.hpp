#pragma once

#include <map>
#include <string>
#include <iostream>

class Client
{
	private:
		std::string	nickname;
		std::string	username;
		std::string	hostname;
		std::string	servername;
		std::string	realname;
		int			fd;

	public:
		Client();
		~Client();
};
