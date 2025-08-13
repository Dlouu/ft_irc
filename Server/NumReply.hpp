#pragma once

#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <netinet/in.h>

#include "./../colors.hpp"
#include "../Client/Client.hpp"
#include "../Server/Server.hpp"

typedef enum	e_NumReply {
	RPL_WELCOME				= 1,
	ERR_NONICKNAMEGIVEN		= 431,
	ERR_ERRONEUSNICKNAME	= 432,
	ERR_NICKNAMEINUSE		= 433
}	t_NumReply;

static const std::map<int, std::string> replyTemplates = {
    { 1,  ":{server} 001 {nick} :Welcome to the IRC Network {nick}!{user}@{host}\r\n" },
    { 431,  ":{server} 431 :No nickname given\r\n" },
    { 432,  ":{server} 432 {nick} :Erroneus nickname\r\n" },
    { 433,  ":{server} 433 {nick} :Nickname is already in use\r\n" },
};
