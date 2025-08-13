#pragma once

#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <netinet/in.h>

#include "./../colors.hpp"
#include "./../errors.hpp"
#include "../Client/Client.hpp"
#include "../Server/Server.hpp"

typedef struct NumReplyData_s {
	std::string	message;
	int			fd;
} NumReplyData_t;

class NumReply
{
	private:
		static NumReply*	_instance;
		void				init( void );

		NumReply();
		~NumReply();
		
	public:
		static NumReply*	GetInstance( void );
};
