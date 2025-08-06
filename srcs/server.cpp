#include "server.hpp"

std::vector<std::string> extractMessages(std::string& buffer) {
	std::vector<std::string> messages;
	size_t pos = 0;
	
	while ((pos = buffer.find("\r\n")) != std::string::npos) {
		messages.push_back(buffer.substr(0, pos + 2));
		buffer.erase(0, pos + 2);
	}
	return messages;
}