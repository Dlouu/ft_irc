#include "parsing.hpp"

void processIRCMessage(int clientFd, const std::string& message) {
	std::cout << ">>> " << message;
	
	std::string cleanMessage = message;
	if (cleanMessage.size() >= 2 && cleanMessage.substr(cleanMessage.size() - 2) == "\r\n") {
		cleanMessage = cleanMessage.substr(0, cleanMessage.size() - 2);
	}
	
	std::string response;
	if (cleanMessage == "CAP LS") {
		response = "CAP * LS :\r\n";
		std::cout << "<<< " << response;
		send(clientFd, response.c_str(), response.length(), 0);
	}
}