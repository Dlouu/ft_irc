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

static std::map<int, std::string>			createReplies( void );
static std::map<std::string, std::string>	fillVars( void );

static std::map<int, std::string> replies;
static std::map<std::string, std::string> vars;

std::string formatReply(int code, const std::map<std::string, std::string> &vars);

//response = formatReply(1, vars);