#pragma once

#include <map>
#include <string>
#include <sstream>

#include "./../colors.hpp"
#include "../Client/Client.hpp"
#include "../Server/Server.hpp"

typedef enum e_NumReply {
	RPL_WELCOME				= 1,
	RPL_YOURHOST			= 2,
	RPL_CREATED				= 3,
	RPL_MYINFO				= 4,
	RPL_AWAY				= 301,
	RPL_NOTOPIC				= 331,
	RPL_TOPIC				= 332,
	RPL_INVITING			= 341,
	RPL_NAMREPLY			= 353,
	ERR_NOSUCHNICK			= 401,
	ERR_NOSUCHCHANNEL		= 403,
	ERR_CANNOTSENDTOCHAN	= 404,
	ERR_TOOMANYCHANNELS		= 405,
	ERR_TOOMANYTARGETS		= 407,
	ERR_NORECIPIENT			= 411,
	ERR_NOTEXTTOSEND		= 412,
	ERR_NOTOPLEVEL			= 413,
	ERR_WILDTOPLEVEL		= 414,
	ERR_NONICKNAMEGIVEN		= 431,
	ERR_ERRONEUSNICKNAME	= 432,
	ERR_NICKNAMEINUSE		= 433,
	ERR_NOTONCHANNEL		= 442,
	ERR_USERONCHANNEL		= 443,
	ERR_NEEDMOREPARAMS		= 461,
	ERR_ALREADYREGISTRED	= 462,
	ERR_CHANNELISFULL		= 471,
	ERR_INVITEONLYCHAN		= 473,
	ERR_BANNEDFROMCHAN		= 474,
	ERR_BADCHANNELKEY		= 475,
	ERR_BADCHANMASK			= 476,
	ERR_CHANOPRIVSNEEDED	= 482
} t_NumReply;

std::map<int, std::string>			createReplies( void );
std::map<std::string, std::string>	fillVars( int clientFD );

extern std::map<int, std::string>			g_replies;
extern std::map<std::string, std::string>	g_vars;

std::string formatReply(int code, const std::map<std::string, std::string> &vars);
