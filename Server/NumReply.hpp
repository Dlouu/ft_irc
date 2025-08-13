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

enum	NumReply {
	RPL_WELCOME		= 001,
};

static const std::map<int, std::string> replyTemplates = {
    { 1,  ":{server} 001 {nick} :Welcome to the IRC Network {nick}!{user}@{host}" },
};
