#include "parsing.hpp"
#include "command.hpp"
#include <algorithm>

void processIRCMessage( int clientFd, const std::string& message ) {
	std::cout << ">>> " << message;
	
	std::string cleanMessage = message;
	if (cleanMessage.size() >= 2 && cleanMessage.substr(cleanMessage.size() - 2) == "\r\n") {
		cleanMessage = cleanMessage.substr(0, cleanMessage.size() - 2);
	}
	Command::handleCommand( cleanMessage, clientFd );
}
