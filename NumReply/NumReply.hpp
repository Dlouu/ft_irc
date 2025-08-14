#pragma once

#include <map>
#include <string>
#include <sstream>

#include "./../colors.hpp"
#include "../Client/Client.hpp"
#include "../Server/Server.hpp"

typedef enum	e_NumReply {
	RPL_WELCOME				= 1,
	ERR_NONICKNAMEGIVEN		= 431,
	ERR_ERRONEUSNICKNAME	= 432,
	ERR_NICKNAMEINUSE		= 433
}	t_NumReply;

std::map<int, std::string>			createReplies( void );
std::map<std::string, std::string>	fillVars( int clientFD );

extern std::map<int, std::string>			g_replies;
extern std::map<std::string, std::string>	g_vars;

std::string formatReply(int code, const std::map<std::string, std::string> &vars);
