#include <map>
#include "NumReply.hpp"

static std::map<int, std::string> createReplies() {
    std::map<int, std::string> num;

    num[RPL_WELCOME] =			":{server} 001 {nick} :Welcome to the IRC Network {nick}!{user}@{host}\r\n";
    num[ERR_NONICKNAMEGIVEN] =	":{server} 431 {nick} :No nickname given\r\n";
	num[ERR_ERRONEUSNICKNAME] =	":{server} 432 {nick} :Erroneous nickname\r\n";
    num[ERR_NICKNAMEINUSE] =	":{server} 433 {nick} :Nickname is already in use\r\n";
    return num;
}

static std::map<std::string, std::string> fillVars() {
	std::map<std::string, std::string> tab;
	
    tab["nick"] =	"Testnick";
    tab["user"] =	"Testuser";
	tab["server"] =	"Testserver";
    tab["host"] =	"Testhost";
    return tab;
}

static std::map<int, std::string> replies = createReplies();
static std::map<std::string, std::string> vars = fillVars();

std::string formatReply(int code, const std::map<std::string, std::string> &vars) {
	std::map<int, std::string>::const_iterator templateIt = replies.find(code);
	if (templateIt == replies.end())
        return "";
	std::string reply = templateIt->second;

	std::map<std::string, std::string>::const_iterator it;
    for (it = vars.begin(); it != vars.end(); ++it) {
        std::string key = "{" + it->first + "}";
        std::string::size_type pos = 0;
        
        while ((pos = reply.find(key, pos)) != std::string::npos) {
            reply.replace(pos, key.length(), it->second);
            pos += it->second.length();
        }
    }
    return reply;
}