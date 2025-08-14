#include <map>
#include "NumReply.hpp"

std::map<int, std::string> createReplies() {
    std::map<int, std::string> num;

    num[RPL_WELCOME] =			":{server} 001 {nick} :Welcome to the IRC Network {nick}!{user}@{host}\r\n";
    num[ERR_NONICKNAMEGIVEN] =	":{server} 431 {nick} :No nickname given\r\n";
	num[ERR_ERRONEUSNICKNAME] =	":{server} 432 {nick} :Erroneous nickname\r\n";
    num[ERR_NICKNAMEINUSE] =	":{server} 433 {nick} :Nickname is already in use\r\n";
    return num;
}

std::map<std::string, std::string> fillVars( int clientFD ) {
	std::map<std::string, std::string> tab;
	
	Client client = Server::GetClientByFD( clientFD );
    tab["nick"] =	client.getNickname();
    tab["user"] =	client.getUsername();
	tab["server"] =	client.getServername();
    tab["host"] =	client.getHostname();
    return tab;
}

std::string formatReply(int code, const std::map<std::string, std::string> &vars) {
	std::map<int, std::string>::const_iterator templateIt = g_replies.find(code);
	if (templateIt == g_replies.end())
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
